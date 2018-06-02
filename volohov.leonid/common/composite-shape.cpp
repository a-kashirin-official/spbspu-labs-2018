#include <stdexcept>
#include "composite-shape.hpp"

using namespace volohov;

CompositeShape::CompositeShape(std::shared_ptr<Shape> shape):
  counter_(0),
  array_(nullptr)
{
  if (!shape)
  {
    throw std::invalid_argument("Empty shape");
  }
  else
  {
    addShape(shape);
  }
}

CompositeShape::CompositeShape(const CompositeShape & compositeshape):
  counter_(compositeshape.counter_)
{
  std::unique_ptr<std::shared_ptr<Shape>[]> temp_array(new std::shared_ptr<Shape>[counter_]);
  for (int i = 0; i < counter_; i ++)
  {
    temp_array[i] = compositeshape.array_[i];
  }
  array_.swap(temp_array);
}

CompositeShape & CompositeShape::operator = (const CompositeShape & compositeshape)
{
  counter_ = compositeshape.counter_;
  array_.reset(new std::shared_ptr <Shape>[counter_]);
  for (int i = 0; i < counter_; i++)
  {
    array_[i] = compositeshape.array_[i];
  }
  return *this;
}

double CompositeShape::getArea() const
{
  double area = 0;
  for (int i = 0; i < counter_; i++)
  {
    area = area + array_[i] -> getArea();
  }
  return(area);
}

rectangle_t CompositeShape::getFrameRect() const
{
  if (counter_ <= 0)
  {
    throw std::invalid_argument("Composite shape is empty");
  }
  else
  {
    rectangle_t rectangle = array_[0] -> getFrameRect();
    double left = rectangle.pos.x + (rectangle.width / 2);
    double top = rectangle.pos.x + (rectangle.height / 2);
    double right = rectangle.pos.x - (rectangle.width / 2);
    double bottom = rectangle.pos.y - (rectangle.height / 2);
    for (int i = 1; i < counter_; i++)
    {
      rectangle = array_[i] -> getFrameRect();
      left = std::max(left, rectangle.pos.x + (rectangle.width / 2));
      top = std::max(top, rectangle.pos.x + (rectangle.height / 2));
      right = std::min(right, rectangle.pos.x - (rectangle.width / 2));
      bottom = std::min(bottom, rectangle.pos.x - (rectangle.height / 2));
    }
    return { {(left + right) / 2, (top + bottom) / 2}, left - right, top - bottom};
  }
}

void CompositeShape::move(const point_t & newCenter)
{
  point_t center = getFrameRect().pos;
  double dx = newCenter.x - center.x;
  double dy = newCenter.y - center.y;
  for (int i= 0; i < counter_; i++)
  {
    array_[i] -> move(dx,dy);
  }
}

void CompositeShape::move(const double dx,const double dy)
{
  for (int i = 0; i < counter_; i++)
  {
    array_[i] -> move(dx,dy);
  }
}

void CompositeShape::scale(const double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Invalid coefficient");
  }
  else
  {
    point_t center = getFrameRect().pos;
    for (int i = 0; i < counter_; i++)
    {
      point_t shape_center = array_[i] -> getFrameRect().pos;
      array_[i] -> move(coefficient * (shape_center.x - center.x),
        coefficient * (shape_center.y - center.y));
      array_[i] -> scale(coefficient);
    }
  }
}

void CompositeShape::addShape(const std::shared_ptr<Shape> newShape)
{
  if (!newShape)
  {
      throw std::invalid_argument("Empty shape");
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> temp_array(new std::shared_ptr<Shape>[counter_ + 1]);
  for (int i = 0; i < counter_; i ++)
  {
    temp_array[i] = array_[i];
  }
  temp_array[counter_ ++] = newShape;
  array_.swap(temp_array);
}

void CompositeShape::removeShape(const int index)
{
  if ((index < 0) || (index >= counter_))
  {
    throw std::invalid_argument("Invalid index");
  }
  if (counter_ <= 0)
  {
    throw std::invalid_argument("Composite shape is empty");
  }
  if (counter_ == 1)
  {
    removeAll();
    return;
  }
  else
  {
    std::unique_ptr<std::shared_ptr<Shape>[]> temp_array(new std::shared_ptr<Shape>[counter_ - 1]);
    for (int i = 0; i < index; i ++)
    {
      temp_array[i] = array_[i];
    }
    for (int i = index; i < counter_ - 1; i ++)
    {
      temp_array[i] = array_[i+1];
    }
    array_.swap(temp_array);
    --counter_;
  }
}

void CompositeShape::removeAll()
{
  array_.reset(nullptr);
  counter_ = 0;
}

int CompositeShape::getCount() const
{
  return counter_;
}
