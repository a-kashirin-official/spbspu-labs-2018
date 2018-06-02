#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>

kadyrov::Circle::Circle(const point_t &centerPos, const double radius) :
  position_(centerPos),
  radius_(radius)
{
  if (radius_ < 0.0)
  {
    throw std::invalid_argument("Wrong value of radius.");
  }
}

double kadyrov::Circle::getArea() const
{
  return radius_ * radius_ * M_PI;
}

kadyrov::rectangle_t kadyrov::Circle::getFrameRect() const
{
  return { radius_ * 2, radius_ * 2, position_ };
}

void kadyrov::Circle::move(const double dx, const double dy)
{
  position_.x += dx;
  position_.y += dy;
}

void kadyrov::Circle::move(const point_t &newPos)
{
  position_ = newPos;
}

void kadyrov::Circle::scale(const double coefficient)
{
  if (coefficient < 0.0)
  {
    throw std::invalid_argument("Wrong value of coefficient.");
  }
  else
  {
    radius_ *= coefficient;
  }
}
