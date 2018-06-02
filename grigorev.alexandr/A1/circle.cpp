#include <cmath>
#include <iostream>
#include "circle.hpp"

Circle::Circle(const point_t & center,const double radius):
  center_(center),
  r_(radius)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Error: Invalid radius");
  }
}

double Circle::getArea() const
{
  return M_PI * r_ * r_;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{center_, 2*r_, 2*r_};
}

void Circle::move(const point_t & newCenter)
{
  center_ = newCenter;
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}
