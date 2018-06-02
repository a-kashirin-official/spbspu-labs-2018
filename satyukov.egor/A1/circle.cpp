#include "circle.hpp"

#include <iostream>
#include <math.h>

Circle::Circle(const point_t & center, const double radius):
  center_(center),
  radius_(radius)
{
  if (radius_ <= 0)
  {
    std::cerr << "Invalid circle radius" << std::endl;
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

double Circle::getRadius() const
{
  return radius_;
}

point_t Circle::getCoordinates() const
{
  return { center_.x, center_.y };
}

rectangle_t Circle::getFrameRect() const
{
  return { center_, 2 * radius_, 2 * radius_ };
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
