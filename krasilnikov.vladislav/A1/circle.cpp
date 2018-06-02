#include "circle.hpp"

#include <iostream>
#include <math.h>

Circle::Circle(const point_t & center, const double radius):
  center_(center),
  radius_(radius)
{
  if (radius_ < 0.0)
  {
    throw std::invalid_argument("Incorrect radius value");
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return { 2 * radius_, 2 * radius_, center_ };
}

void Circle::move(const point_t & newPosition)
{
  center_ = newPosition;
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}
