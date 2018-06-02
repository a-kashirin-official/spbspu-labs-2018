#include <iostream>
#include <memory>
#include <cmath>

#include "composite-shape.hpp"

using namespace stashevskii;

CompositeShape::CompositeShape() : 
  shapes_(nullptr),
  amount_(0)
{

}

CompositeShape::CompositeShape(const std::shared_ptr< Shape > &shape):
  shapes_(nullptr),
  amount_(0)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("invalid pointer");
  }
  addShape(shape);
}

CompositeShape::CompositeShape(const CompositeShape & copyShape):
  shapes_(new std::shared_ptr< Shape > [copyShape.amount_]),
  amount_(copyShape.amount_)
{
  for (int i = 0; i < amount_; ++i)
  {
    shapes_[i] = copyShape.shapes_[i];
  }
}

CompositeShape::CompositeShape(CompositeShape && moveShape):
  shapes_(nullptr),
  amount_(0)
{
  if(this != &moveShape)
  {
    shapes_.swap(moveShape.shapes_);
    amount_ = moveShape.amount_;
    moveShape.amount_ = 0;
    moveShape.shapes_.reset();
  }
}

CompositeShape & CompositeShape::operator = (const CompositeShape & copyShape)
{
  if (this != & copyShape)
  {
    int amountT = copyShape.amount_;
    shapes_.reset(new std::shared_ptr< Shape >[amountT]);
    amount_ = copyShape.amount_;
    for (int i = 0; i < amount_; ++i)
    {
      shapes_[i] = copyShape.shapes_[i];
    }
  }
  return *this;
}

CompositeShape & CompositeShape::operator= (CompositeShape && moveShape)
{
  if(this != &moveShape)
  {
    shapes_.swap(moveShape.shapes_);
    amount_ = moveShape.amount_;
    moveShape.amount_ = 0;
    moveShape.shapes_.reset();
  }
  return *this;
}

rectangle_t CompositeShape::getFrameRect() const
{
  if (amount_ == 0)
  {
    return {0,0,{0,0}};
  }
  else
  {
    rectangle_t frame = shapes_[0]->getFrameRect();
    double right = frame.pos.x + frame.width / 2.0;
    double left = frame.pos.x - frame.width / 2.0;
    double top = frame.pos.y + frame.height / 2.0;
    double bottom = frame.pos.y - frame.height / 2.0;
    for(int i = 1; i < amount_; ++i)
    {
      frame = shapes_[i]->getFrameRect();
      double right_ = frame.pos.x + frame.width / 2.0;
      double left_ = frame.pos.x - frame.width / 2.0;
      double top_ = frame.pos.y + frame.height / 2.0;
      double bottom_ = frame.pos.y - frame.height / 2.0;
      
      if(right_ > right)
      {
        right = right_;
      }
      if(left_ < left)
      {
        left = left_;
      }
      if(top_ > top)
      {
        top = top_;
      }
      if(bottom_ < bottom)
      {
        bottom = bottom_;
      }
    }
    return {(top - bottom),(right - left),{((right + left) / 2.0),((top + bottom) / 2.0)}};
  }
}


double CompositeShape::getArea() const
{
  double shapes_Area = 0;
  for (int i = 0; i < amount_; ++i)
  {
    shapes_Area += shapes_[i]->getArea();
  }
  return shapes_Area;
}

void CompositeShape::move(const double dx, const double dy)
{
  for (int i = 0; i < amount_; i++)
  {
    shapes_[i]->move(dx, dy);
  }
}


void CompositeShape::move(const point_t &Point)
{
  const point_t point = getFrameRect().pos;
  move(Point.x - point.x, Point.y - point.y);
}

void CompositeShape::scale(const double k)
{
  if (k < 0.0)
  {
    throw std::invalid_argument("invalid argument k");
  }
  point_t point = getFrameRect().pos;
  for(int i = 0;i < amount_; i++)
  {
    shapes_[i]->move({k*(shapes_[i]->getFrameRect().pos.x-point.x)+point.x,
        k*(shapes_[i]->getFrameRect().pos.y-point.y)+point.y});
    shapes_[i]->scale(k);
  }
}

void CompositeShape::printf() const
{
  std::cout << "Composite Shape" << std::endl;
  std::cout << "amount_: " << amount_ << std::endl;
}

point_t CompositeShape::getPosition() const
{
  return getFrameRect().pos;
}


void CompositeShape::addShape(const std::shared_ptr <Shape> new_shape)
{
  if(new_shape == nullptr)
  {
    throw std::invalid_argument("invalid shape pointer");
  }
  for(int i = 0; i < amount_; ++i)
  {
    if (new_shape == shapes_[i])
    {
      throw std::invalid_argument("this shape is already exist");
    }
  }
  std::unique_ptr< std::shared_ptr< Shape > [] > newshapes_(new std::shared_ptr< Shape >[amount_ + 1]);
  for(int i = 0; i < amount_; i++)
  {
    newshapes_[i] = shapes_[i];
  }
  newshapes_[amount_++] = new_shape;
  shapes_.swap(newshapes_);
}

void CompositeShape::deleteShape(const int number)
{
  if(amount_ == 0)
  {
    throw std::out_of_range("Wrong amount_ of shapes_");
  }
  else
  {
    if ((number >= amount_) || (number <=0))
    {
      throw std::out_of_range("Wrong number of shapes_");
    }
  }
  if(amount_ == 1)
  {
    deleteAll();
  }
  else
  {
    std::unique_ptr< std::shared_ptr< Shape > [] > newshapes_(new std::shared_ptr< Shape >[amount_ - 1]);
    for(int i = 0; i < (number-1);++i)
  {
    newshapes_[i] = shapes_[i];
  }
  for(int i = number; i < amount_;++i)
  {
    newshapes_[i-1] = shapes_[i];
  }
    shapes_.swap(newshapes_);
    --amount_;
  }
}

void CompositeShape::deleteAll()
{
  shapes_.reset();
  shapes_ = nullptr;
  amount_ = 0;
}

std::shared_ptr< Shape > & CompositeShape::operator[](int size)
{
  if (size < 0)
  {
    throw std::out_of_range("Size of the array must be != 0");
  }
  if (size >= amount_)
  {
    throw std::out_of_range("Size of the array must be less than size of the container!");
  }
  return shapes_[size];
}

int CompositeShape::getArraySize() const
{
  return amount_;
}

void CompositeShape::rotate(const double angle)
{
  for(int i=0; i < amount_; i++)
  {
    shapes_[i]->rotate(angle);
    const double delta_x = shapes_[i]->getFrameRect().pos.x -getFrameRect().pos.x;
    const double delta_y = shapes_[i]->getFrameRect().pos.y -getFrameRect().pos.y;
    shapes_[i]->move( delta_x*cos(angle) - delta_y*sin(angle), delta_y*cos(angle) + delta_x*sin(angle));
  }
}
