#include "composite-shape.hpp"
#include <stdexcept>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace shumkovskaya;

shumkovskaya::CompositeShape::CompositeShape(std::shared_ptr<shumkovskaya::Shape> shape) :
  amount_(0),
  array_(nullptr),
  angle_(0.0)
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

shumkovskaya::CompositeShape::CompositeShape(const shumkovskaya::CompositeShape & rhs) :
  amount_(rhs.amount_),
  array_(new std::shared_ptr<shumkovskaya::Shape>[rhs.amount_])
{
  for (int i = 0; i < rhs.amount_; i++)
  {
    array_[i] = rhs.array_[i];
  }
}

shumkovskaya::CompositeShape & CompositeShape::operator = (const shumkovskaya::CompositeShape & rhs)
{
  amount_ = rhs.amount_;
  array_.reset(new std::shared_ptr <shumkovskaya::Shape>[amount_]);
  for (int i = 0; i < amount_; i++)
  {
    array_[i] = rhs.array_[i];
  }
  return *this;
}

std::shared_ptr<shumkovskaya::Shape > shumkovskaya::CompositeShape::operator[](int index) const
{
  if ((index < 0) || (index >= amount_))
  {
    throw std::out_of_range("invalid index");
  }
  return array_[index];
}

double shumkovskaya::CompositeShape::getArea() const noexcept
{
  double area = 0;
  for (int i = 0; i < amount_; i++)
  {
    area = area + array_[i]->getArea();
  }
  return(area);
}

shumkovskaya::rectangle_t shumkovskaya::CompositeShape::getFrameRect() const
{
  if (amount_ <= 0)
  {
    throw std::invalid_argument("Composite shape is empty");
  }
  else
  {
    shumkovskaya::rectangle_t rect = array_[0]->getFrameRect();
    double left = rect.pos.x - rect.width / 2;
    double right = rect.pos.x + rect.width / 2;
    double top = rect.pos.y + rect.height / 2;
    double bottom = rect.pos.y - rect.height / 2;
    for (int i = 1; i < amount_; i++)
    {
      rect = array_[i]->getFrameRect();
      left = std::min(left, rect.pos.x - rect.width / 2);
      top = std::max(top, rect.pos.y + rect.height / 2);
      right = std::max(right, rect.pos.x + rect.width / 2);
      bottom = std::min(bottom, rect.pos.y - rect.height / 2);
    }
    return { right - left, top - bottom,{ (left + right) / 2, (top + bottom) / 2 } };
  }
}

void shumkovskaya::CompositeShape::move(const shumkovskaya::point_t & p) noexcept
{
  move(p.x - getFrameRect().pos.x, p.y - getFrameRect().pos.y);
}

void shumkovskaya::CompositeShape::move(const double dx, const double dy) noexcept
{
  for (int i = 0; i < amount_; i++)
  {
    array_[i]->move(dx, dy);
  }
}

void shumkovskaya::CompositeShape::scale(const double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Wrong coefficient");
  }
  else
  {
    shumkovskaya::point_t center = getFrameRect().pos;
    for (int i = 0; i < amount_; i++)
    {
      shumkovskaya::point_t shape_center = array_[i]->getFrameRect().pos;
      array_[i]->move((coefficient-1) * (shape_center.x - center.x),
        (coefficient -1)* (shape_center.y - center.y));
      array_[i]->scale(coefficient);
    }
  }
}

void shumkovskaya::CompositeShape::rotate(const double angle) noexcept
{
  shumkovskaya::point_t centre = CompositeShape::getFrameRect().pos;
  const double sin_a = std::sin((angle * M_PI) / 180);
  const double cos_a = std::cos((angle * M_PI) / 180);
  for (int i = 0; i < amount_; i++)
  {
    shumkovskaya::point_t centre_shape = array_[i]->getFrameRect().pos;
    array_[i]->move({ centre.x + (centre_shape.x - centre.x) * cos_a - (centre_shape.y - centre.y) * sin_a,
      centre.y + (centre_shape.y - centre.y) * cos_a + (centre_shape.x - centre.x) * sin_a });
    array_[i]->rotate(angle);
  }
  angle_ += angle;
  angle_ = fmod(angle_, 360.0);
}

void shumkovskaya::CompositeShape::addShape(const std::shared_ptr<shumkovskaya::Shape> newShape)
{
  if (!newShape)
  {
    throw std::invalid_argument("Empty shape");
  }
  for (int i = 0; i < amount_; i++)
  {
    if (newShape == array_[i])
    {
      throw std::invalid_argument("This shape already added");
    }
  }
  std::unique_ptr<std::shared_ptr<shumkovskaya::Shape>[]> temp_array
    (new std::shared_ptr<shumkovskaya::Shape>[amount_ + 1]);
  for (int i = 0; i < amount_; i++)
  {
    temp_array[i] = array_[i];
  }
  temp_array[amount_++] = newShape;
  array_.swap(temp_array);
}

void shumkovskaya::CompositeShape::removeShape(const int index)
{
  if ((index < 0) || (index >= amount_))
  {
    throw std::invalid_argument("Wrong index");
  }
  if (amount_ <= 0)
  {
    throw std::invalid_argument("Composite shape is empty");
  }
  if (amount_ == 1)
  {
    removeAll();
    return;
  }
  else
  {
    std::unique_ptr<std::shared_ptr<shumkovskaya::Shape>[]> temp_array
      (new std::shared_ptr<shumkovskaya::Shape>[amount_ - 1]);
    for (int i = 0; i < index; i++)
    {
      temp_array[i] = array_[i];
    }
    for (int i = index; i < amount_ - 1; i++)
    {
      temp_array[i] = array_[i + 1];
    }
    array_.swap(temp_array);
    --amount_;
  }
}

void shumkovskaya::CompositeShape::removeAll()
{
  array_.reset(nullptr);
  amount_ = 0;
}

int shumkovskaya::CompositeShape::getAmount() const
{
  return amount_;
}
