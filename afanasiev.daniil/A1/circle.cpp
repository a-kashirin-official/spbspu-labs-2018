#include "circle.hpp"

#include <iostream>
#include <math.h>

Circle::Circle(const point_t & center, const double radius):
  center_(center),
  radius_(radius)
{
  if (radius_ < 0.0)
  {
    throw std::invalid_argument("Radius must be > 0.0");
  }
}

double Circle::getArea() const noexcept
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const noexcept
{
  return { 2 * radius_, 2 * radius_, center_ };
}

void Circle::move(const point_t & newPos) noexcept
{
  center_ = newPos;
}

void Circle::move(const double dx, const double dy) noexcept
{
  center_.x += dx;
  center_.y += dy;
}
