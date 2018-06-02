#include "composite-shape.hpp"

#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <stdexcept>

semakina::CompositeShape::CompositeShape(const std::shared_ptr <semakina::Shape> shape):
  counter_(0),
  degree_(0),
  array_(nullptr)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid_pointer");
  }
  addShape(shape);
}

semakina::CompositeShape::CompositeShape(const semakina::CompositeShape & compositeshape):
  counter_(compositeshape.counter_)
{
  array_ = std::unique_ptr <std::shared_ptr <semakina::Shape>[]>(new std::shared_ptr <semakina::Shape>[counter_]);
  for (int i = 0; i < counter_; i++)
  {
    array_[i] = compositeshape.array_[i];
  }
}

semakina::CompositeShape & semakina::CompositeShape::operator = (const semakina::CompositeShape & compositeshape) noexcept
{
  if (this != & compositeshape)
  {
    counter_ = compositeshape.counter_;
    array_.reset(new std::shared_ptr <semakina::Shape>[counter_]);
    for (int i = 0; i < counter_; i++)
    {
      array_[i] = compositeshape.array_[i];
    }
  }
  return * this;
}

std::shared_ptr<semakina::Shape> semakina::CompositeShape::operator[](const int index) const
{
  if ((index >= counter_) || (index < 0))
  {
    throw std::out_of_range("Index is out of range");
  }
  return array_[index];
}


double semakina::CompositeShape::getArea() const noexcept
{
  double area = 0;
  for (int i = 0; i < counter_; i++)
  {
    area += array_[i] -> getArea();
  }
  return area;
}

semakina::rectangle_t semakina::CompositeShape::getFrameRect() const noexcept
{
  if (counter_ == 0)
  {
      return {0, 0, {0, 0}};
  }
  else
  {
    semakina::rectangle_t rect = array_[0] -> getFrameRect();
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
    return {max_x - min_x, max_y - min_y, {(max_x + min_x) / 2, (max_y + min_y) / 2}};
  }
}

void semakina::CompositeShape::move(const double dx, const double dy) noexcept
{
  for (int i = 0; i < counter_; i++)
  {
    array_[i] -> move(dx,dy);
  }
}

void semakina::CompositeShape::move(const point_t & pos) noexcept
{
  point_t centre = getFrameRect().pos;
  double dx = pos.x - centre.x;
  double dy = pos.y - centre.y;
  for (int i= 0; i < counter_; i++)
  {
    array_[i] -> move(dx,dy);
  }
}

void semakina::CompositeShape::scale(const double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Invalid_coefficient");
  }
  semakina::point_t centre = getFrameRect().pos;
  for (int i = 0; i < counter_; i++)
  {
    semakina::point_t shape_centre = array_[i] -> getFrameRect().pos;
    array_[i] -> move((shape_centre.x - centre.x) * coefficient,
      (shape_centre.y - centre.y) * coefficient);
    array_[i] -> scale(coefficient);
  }
}

void semakina::CompositeShape::rotate(const double degree) noexcept
{
  degree_ += degree;
  for (int i = 0; i < counter_; ++i)
  {
    array_[i] -> rotate(degree);
    array_[i] -> move((array_[i]->getFrameRect().pos.x - getFrameRect().pos.x) * cos(degree_ * M_PI / 180) -
      (array_[i]->getFrameRect().pos.y - getFrameRect().pos.y) * sin(degree_ * M_PI / 180),
        (array_[i]->getFrameRect().pos.y - getFrameRect().pos.y) * cos(degree_ * M_PI / 180) +
          (array_[i]->getFrameRect().pos.x - getFrameRect().pos.x) * sin(degree_ * M_PI / 180));
  }
}

void semakina::CompositeShape::addShape(const std::shared_ptr <semakina::Shape> shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Invalid_pointer");
  }
  std::unique_ptr < std::shared_ptr < semakina::Shape>[] > array(new std::shared_ptr < semakina::Shape >[counter_ + 1]);
  for (int i = 0; i < counter_; i++)
  {
    array[i] = array_[i];
  }
  array[counter_++] = shape;
  array_.swap(array);
}

void semakina::CompositeShape::deleteShape(const int i)
{
  if (counter_ == 0)
  {
    throw std::out_of_range("Composite Shape is empty");
  }
  if ((i >= counter_) || (i < 0))
  {
    throw std::invalid_argument("Invalid_index");
  }
  else if (counter_ > 0)
  {
    std::unique_ptr < std::shared_ptr < semakina::Shape >[] > array(new std::shared_ptr < semakina::Shape >[counter_ - 1]);
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

void semakina::CompositeShape::clear() noexcept
{
  counter_ = 0;
  array_.reset(nullptr);
}

int semakina::CompositeShape::getCounter() const noexcept
{
  return counter_;
}
