#include <iostream>
#include <stdexcept>
#include "composite-shape.hpp"
#include <memory>

using namespace zasyadko;

CompositeShape::CompositeShape(const std::shared_ptr< Shape > shape):
  shapes(nullptr),
  amount(0)
{
  if(shape == nullptr)
  {
    throw std::invalid_argument("invalid pointer");
  }
  addShape(shape);
}

CompositeShape::CompositeShape(const CompositeShape & copyshape):
  shapes(new std::shared_ptr< Shape >[copyshape.amount]),
  amount(copyshape.amount)
{
  for (int i = 0;i < amount;++i)
  {
    shapes[i] = copyshape.shapes[i];
  }
}

CompositeShape::CompositeShape(CompositeShape && moveShape):
  shapes(nullptr),
  amount(0)
{
  if(this != &moveShape)
  {
    shapes.swap(moveShape.shapes);
    amount = moveShape.amount;
    moveShape.amount = 0;
    moveShape.shapes.reset();
  }
  else
  {
    throw std::invalid_argument("invalid shape");
  }
}

CompositeShape & CompositeShape::operator= (const CompositeShape & copyshape)
{
  if(this == & copyshape)
  {
    return *this;
  }
  shapes.reset(new std::shared_ptr<Shape> [copyshape.amount] );
  amount = copyshape.amount;
  for (int i = 0; i < amount ; ++i)
  {
    shapes[i] = copyshape.shapes[i];
  }
    
  return *this;
}

CompositeShape & CompositeShape::operator= (CompositeShape && moveShape)
{
  if(this == &moveShape)
  {
    return *this;
  }
  shapes.reset(new std::shared_ptr<Shape> [moveShape.amount] );
  shapes = std::move(moveShape.shapes);
  amount = moveShape.amount;
  moveShape.amount = 0;
  moveShape.shapes.reset();
  
  return *this;
}
  

double CompositeShape::getArea() const
{
  double shapesArea = 0;
  for (int i = 0; i < amount; ++i)
  {
    shapesArea += shapes[i]->getArea();
  }
  return shapesArea;
}

rectangle_t CompositeShape::getFrameRect() const
{
  if (amount == 0)
  {
    return {{0,0},0,0};
  }
  else
  {
    rectangle_t frame = shapes[0]->getFrameRect();
    double right = frame.pos.x + frame.width / 2.0;
    double left = frame.pos.x - frame.width / 2.0;
    double top = frame.pos.y + frame.height / 2.0;
    double bottom = frame.pos.y - frame.height / 2.0;
    for(int i = 1; i < amount; ++i)
    {
      frame = shapes[i]->getFrameRect();
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
  return {{((right + left) / 2.0),((top + bottom) / 2.0)},(top - bottom),(right - left)};
}
}

void CompositeShape::print() const
{
  std::cout << "Composite Shape" << std::endl;
}

void CompositeShape::move(const point_t & Center)
{
  const point_t centre = getFrameRect().pos;
  move(Center.x - centre.x, Center.y - centre.y);
}

void CompositeShape::move(const double add_x, const double add_y)
{
  for (int i = 0; i < amount; i++)
  {
    shapes[i]->move(add_x, add_y);
  }
}

void CompositeShape::addShape(const std::shared_ptr <Shape> new_shape)
{
  if(new_shape == nullptr)
  {
    throw std::invalid_argument("invalid pointer on shape");
  }
  for(int i = 0; i < amount; ++i)
  {
  if (new_shape == shapes[i])
  {
    throw std::invalid_argument("this shape is already in this comp. shape");
  }
  }
  std::unique_ptr< std::shared_ptr< Shape >[] > newshapes(new std::shared_ptr< Shape >[amount + 1]);
  for(int i = 0; i < amount; i++)
  {
    newshapes[i] = shapes[i];
  }
  newshapes[amount++] = new_shape;
  shapes.swap(newshapes);
}

void CompositeShape::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Invalid factor");
  }
  point_t center = getFrameRect().pos;
  for(int i = 0;i < amount; i++)
  {
    shapes[i]->move({factor*(shapes[i]->getFrameRect().pos.x-center.x)+center.x,
      factor*(shapes[i]->getFrameRect().pos.y-center.y)+center.y});
    shapes[i]->scale(factor);
  }
}

std::shared_ptr<Shape> CompositeShape::getShapeInfo(const int number) const
{
  return shapes[number];
}

void CompositeShape::deleteShape(const int number)
{
  if(amount == 0)
  {
    throw std::out_of_range("invalid number");
  }
  else
  {
    if ((number >= amount) || (number <=0))
    {
      throw std::invalid_argument("Number of shape is invalid");
    }
  }
  if(amount == 1)
  {
    deleteAll();
  }
  else
  {
  std::unique_ptr< std::shared_ptr< Shape >[] > newshapes(new std::shared_ptr< Shape >[amount - 1]);
  for(int i = 0; i < (number-1);++i)
  {
    newshapes[i] = shapes[i];
  }
  for(int i = number; i < amount;++i)
  {
    newshapes[i-1] = shapes[i];
  }
  shapes.swap(newshapes);
  --amount;
  }
}

void CompositeShape::deleteAll()
{
  shapes.reset();
  shapes = nullptr;
  amount = 0;
}
int CompositeShape::getAmount() const
{
  return amount;
}
