#include "composite-shape.hpp"
#include <stdexcept>
#include <algorithm>

kulikov::CompositeShape::CompositeShape(const std::shared_ptr <kulikov::Shape> shape):
  counter_(0),
  array_(nullptr)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid pointer");
  }
  addShape(shape);
}

kulikov::CompositeShape::CompositeShape(const kulikov::CompositeShape & compositeShape):
  counter_(compositeShape.counter_)
{
  array_ = std::unique_ptr <std::shared_ptr <Shape>[]>(new std::shared_ptr <kulikov::Shape>[counter_]);
  for (int i = 0; i < counter_; i++)
  {
    array_[i] = compositeShape.array_[i];
  }
}

kulikov::CompositeShape & kulikov::CompositeShape::operator = (const kulikov::CompositeShape & compositeShape)
{
  if (this != & compositeShape)
  {
    counter_ = compositeShape.counter_;
    array_.reset(new std::shared_ptr <kulikov::Shape>[counter_]);
    for (int i = 0; i < counter_; i++)
    {
      array_[i] = compositeShape.array_[i];
    }
  }
  return * this;
}

double kulikov::CompositeShape::getArea() const
{
  double area = 0.0;
  for (int i = 0; i < counter_; i++)
  {
    area += array_[i] -> getArea();
  }
  return area;
}

kulikov::rectangle_t kulikov::CompositeShape::getFrameRect() const
{
  if (counter_ == 0)
  {
      return {{0.0, 0.0}, 0.0, 0.0};
  }
  else
  {
    rectangle_t rect = array_[0] -> getFrameRect();
    double max_x = rect.pos.x + (rect.width / 2);
    double max_y = rect.pos.x + (rect.height / 2);
    double min_x = rect.pos.x - (rect.width / 2);
    double min_y = rect.pos.y - (rect.height / 2);
    for (int i = 1; i < counter_; i++)
    {
      rect = array_[i] -> getFrameRect();
      max_x = std::max(max_x, rect.pos.x + (rect.width / 2));
      max_y = std::max(max_y, rect.pos.x + (rect.height / 2));
      min_x = std::min(min_x, rect.pos.x - (rect.width / 2));
      min_y = std::min(min_y, rect.pos.x - (rect.height / 2));
    }
      return {{max_x - min_x, max_y - min_y}, (max_x + min_x) / 2, (max_y + min_y) / 2};
  }
}

void kulikov::CompositeShape::move(const double dx, const double dy)
{
  for (int i = 0; i < counter_; i++)
  {
    array_[i] -> move(dx,dy);
  }
}

void kulikov::CompositeShape::move(const point_t & p)
{
  point_t centre = getFrameRect().pos;
  double dx = p.x - centre.x;
  double dy = p.y - centre.y;
  for (int i= 0; i < counter_; i++)
  {
    array_[i] -> move(dx,dy);
  }
}

void kulikov::CompositeShape::scale(const double koeff)
{
  if (koeff <= 0.0)
  {
    throw std::invalid_argument("Invalid koefficient");
  }
  point_t centre = getFrameRect().pos;
  for (int i = 0; i < counter_; i++)
  {
    point_t shape_centre = array_[i] -> getFrameRect().pos;
    array_[i] -> move((shape_centre.x - centre.x) * koeff,
      (shape_centre.y - centre.y) * koeff);
    array_[i] -> scale(koeff);
  }
}

void kulikov::CompositeShape::addShape(const std::shared_ptr <Shape> shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid pointer");
  }
  std::unique_ptr < std::shared_ptr < Shape>[] > array(new std::shared_ptr < Shape >[counter_ + 1]);
  for (int i = 0; i < counter_; i++)
  {
    array[i] = array_[i];
  }
  array[counter_++] = shape;
  array_.swap(array);
}

void kulikov::CompositeShape::deleteShape(const int i)
{
  if (counter_ == 0)
  {
    throw std::out_of_range("Composite Shape is empty");
  }
  if ((i >= counter_) || (i < 0))
  {
    throw std::invalid_argument("Invalid index");
  }
  else if (counter_ > 0)
  {
    std::unique_ptr < std::shared_ptr < Shape >[] > array(new std::shared_ptr < Shape >[counter_ - 1]);
    for (int j = 0; j < i; j++)
    {
      array[j] = array_[j];
    }
    for (int j = i; j < counter_ - 1; j++)
    {
      array[j] = array_[j+1];
    }
    array_.swap(array);
    --counter_;
  }
}

void kulikov::CompositeShape::clear()
{
  counter_ = 0;
  array_.reset(nullptr);
}

int kulikov::CompositeShape::getCounter() const
{
  return counter_;
}
