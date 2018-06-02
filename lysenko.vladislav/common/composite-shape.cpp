#include <iostream>
#include <memory>
#include "composite-shape.hpp"

using namespace lysenko;

CompositeShape::CompositeShape(const std::shared_ptr <Shape> newShape):
  array_(nullptr),
  size_(0)
{
  if (newShape == nullptr)
  {
    throw std::invalid_argument("Invalid Pointer");
  }
  addShape(newShape);
}

CompositeShape::CompositeShape(const CompositeShape & copyShape):
  size_(copyShape.size_)
{
  std::unique_ptr<std::shared_ptr<Shape> []> tempArray (new std::shared_ptr<Shape>[size_]);
  for (int i = 0; i < copyShape.size_; i++)
  {
    tempArray[i] = copyShape.array_[i];
  }
  array_.swap(tempArray);
}

CompositeShape::CompositeShape(CompositeShape && moveShape):
  size_(moveShape.size_)
{
  array_.swap(moveShape.array_);
  moveShape.size_ = 0;
  moveShape.array_=(nullptr);
}

CompositeShape & CompositeShape::operator= (const CompositeShape & copyShape)
{
  if (this != &copyShape)
  {
    std::unique_ptr <std::shared_ptr<Shape> []> tempArray (new std::shared_ptr<Shape>[copyShape.size_]);
    size_ = copyShape.size_;
    for (int i = 0; i < size_; i++)
    {
      tempArray[i] = copyShape.array_[i];
    }
    array_.swap(tempArray);
  }
  return *this;
}

CompositeShape & CompositeShape::operator= (CompositeShape && moveShape)
{
  if (this != & moveShape)
  {
    size_ = moveShape.size_;
    array_.swap(moveShape.array_);
    moveShape.size_ = 0;
    moveShape.array_ = (nullptr);
  }
  return *this;
}

int CompositeShape::getSize()
{
  return size_;
}

std::shared_ptr<Shape> & CompositeShape::operator[] (const int numb)
{
  if (numb >= size_)
  {
    std::out_of_range("Number is out of array");
  }
  return array_[numb];
}

double CompositeShape::getArea() const
{
  double area = 0.0;
  for (int i = 0; i < size_; i++)
  {
    area += array_[i]->getArea();
  }
  return area;
}

rectangle_t CompositeShape::getFrameRect() const
{
  if (size_ == 0)
  {
    return {{0,0}, 0, 0};
  }
  else
  {
    rectangle_t frameRect = array_[0]->getFrameRect();
    double left = frameRect.pos.x - frameRect.width / 2.0;
    double right = frameRect.pos.x + frameRect.width / 2.0;
    double top = frameRect.pos.y + frameRect.height / 2.0;
    double bottom = frameRect.pos.y - frameRect.height / 2.0;
    for (int i = 1; i < size_; i++)
    {
      frameRect = array_[i]->getFrameRect();
      double left_ = frameRect.pos.x - frameRect.width / 2.0;
      double right_ = frameRect.pos.x + frameRect.width / 2.0;
      double top_ = frameRect.pos.y + frameRect.height / 2.0;
      double bottom_ = frameRect.pos.y - frameRect.height / 2.0;
      if (left_ < left)
      {
        left = left_;
      }
      if (right_ > right)
      {
        right = right_;
      }
      if (top_ > top)
      {
        top = top_;
      }
      if (bottom_ < bottom)
      {
        bottom = bottom_;
      }
    }
    return {{(right + left) / 2, (top + bottom) / 2}, (top - bottom), (right - left)};
  }
}

void CompositeShape::move(const point_t & newCenterPoint)
{
  const point_t currCenter = getFrameRect().pos;
  move(newCenterPoint.x - currCenter.x, newCenterPoint.y - currCenter.y);
}

void CompositeShape::move(const double dx, const double dy)
{
  for (int i = 0; i < size_; i++)
  {
    array_[i]->move(dx, dy);
  }
}

void CompositeShape::scale(const double dk)
{
  if (dk < 0.0)
  {
    throw std::invalid_argument("Coeff can't be negative");
  }
  const double xO = getFrameRect().pos.x;
  const double yO = getFrameRect().pos.y;
  for (int i = 0; i < size_; i++)
  {
    array_[i]->scale(dk);
    double dx = array_[i]->getFrameRect().pos.x - xO;
    double dy = array_[i]->getFrameRect().pos.y - yO;
    array_[i]->move(dx*(dk-1), dy*(dk-1));
  }
}

void CompositeShape::addShape(const std::shared_ptr<Shape> new_shape)
{
  if (new_shape == nullptr)
  {
    throw std::invalid_argument("Invalid pointer");
  }
  for (int i = 0; i < size_; i++)
  {
    if (new_shape == array_[i])
    {
      throw std::invalid_argument("The same shape");
    }
  }
  std::unique_ptr<std::shared_ptr<Shape> []> tempArray (new std::shared_ptr<Shape> [size_ + 1]);
  for (int i = 0; i < size_; i++)
  {
    tempArray[i] = array_[i];
  }
  tempArray[size_] = new_shape;
  array_.swap(tempArray);
  size_++;
}
