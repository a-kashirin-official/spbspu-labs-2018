#include <iostream>
#include "composite-shape.hpp"

using namespace vlasov;

CompositeShape::CompositeShape(const std::shared_ptr<Shape> newshape):
  size_(0),
  shapeArr_(nullptr)
{
  if (newshape == nullptr)
  {
    throw std::invalid_argument("Invalid shape");
  }
  addShape(newshape);
}

CompositeShape::CompositeShape():
  size_(0),
  shapeArr_(nullptr)
{}

double CompositeShape::getArea() const
{
  double area = 0.0;
  for (int i = 0; i<size_; i++)
  {
    area += shapeArr_[i] -> getArea();
  }
  return area;
}

rectangle_t CompositeShape::getFrameRect() const
{
  rectangle_t param = shapeArr_[0]->getFrameRect();
  double left = param.pos.x - param.width / 2;
  double right = param.pos.x + param.width / 2;
  double top = param.pos.y + param.height / 2;
  double bottom = param.pos.y - param.height / 2;

  for (int i = 0; i < size_; i++)
  {
    param = shapeArr_[i]->getFrameRect();
    if (left > param.pos.x - param.width / 2)
    {
      left = param.pos.x - param.width / 2;
    }
    if (right < param.pos.x + param.width / 2)
    {
      right = param.pos.x + param.width / 2;
    }
    if (top < param.pos.y + param.height / 2)
    {
      top = param.pos.y + param.height / 2;
    }
    if (bottom > param.pos.y - param.height / 2)
    {
      bottom = param.pos.y - param.height / 2;
    }
  }
  double width = right - left;
  double height = top - bottom;
  point_t centre = {right - width / 2, top - height / 2};

  return {width, height, centre};
}

void CompositeShape::move(const point_t &poss)
{
  double dx = poss.x - getFrameRect().pos.x;
  double dy = poss.y - getFrameRect().pos.y;
  for (int i = 0; i < size_; i++)
  {
    shapeArr_[i] -> move(dx,dy);
  }
}

void CompositeShape::move(const double xOffset, const double yOffset)
{
  for (int i = 0; i<size_; i++)
  {
    shapeArr_[i] -> move(xOffset,yOffset);
  }
}

void CompositeShape::scale(const double coef_)
{
  if (coef_ < 0.0)
  {
    throw std::invalid_argument("Scaling coef. must be >0");
  }
  for (int i = 0; i<size_; i++ )
  {
    shapeArr_[i]->scale(coef_);
  }
}

void CompositeShape::addShape(const std::shared_ptr<Shape> newShape)
{
  if (newShape == nullptr)
  {
    throw std::invalid_argument("Invalid shape");
  }
  std::unique_ptr<std::shared_ptr <Shape> []> tempArr(new std::shared_ptr<Shape>[size_ + 1]);
  for (int i = 0; i<size_; i++)
  {
    tempArr[i] = shapeArr_[i];
  }
  tempArr[size_] = newShape;
  shapeArr_.swap(tempArr);
  size_++;
}

void CompositeShape::removeShape(const int index)
{
  if (index > size_ -1 || index < 0 || size_ == 1)
  {
    throw std::invalid_argument("Bad index");
  }
  size_ --;
  std::unique_ptr<std::shared_ptr<Shape> []> tmp (new std::shared_ptr<Shape> [size_]);
  int i = 0;
  for (int a = 0; a < size_ + 1; a++)
  {
    if (a != index)
    {
      tmp[i] = shapeArr_[a];
      i++;
    }
  }
  shapeArr_.swap(tmp);
}
