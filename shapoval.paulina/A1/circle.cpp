#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

Circle::Circle(const point_t & centre, const double radius) :
  centre_(centre),
  radius_(radius)
{
  if (radius < 0)
  {
    throw std::invalid_argument("Invalid circle!!");
  }
}

double Circle::getArea() const
{
  return radius_ * radius_ * M_PI;
}

rectangle_t Circle::getFrameRect() const
{
  return {centre_, 2 * radius_, 2 * radius_};
}

void Circle::move(const point_t & new_centre)
{
  centre_ = new_centre;
}

void Circle::move(const double dx, const double dy)
{
  centre_.x += dx;
  centre_.y += dy;
}
