#include "circle.hpp"

#include <iostream>
#include <math.h>

Circle::Circle(const point_t & center, const double radius) :
  center_(center),
  radius_(radius)
  
{
  if (radius_ < 0)
  {
    std::cerr << "Invalid_radius" << std::endl;
  }
}

double Circle::getArea() const
{
  return M_PI * pow(radius_, 2);
}

rectangle_t Circle::getFrameRect() const
{ 
  return { center_, 2 * radius_, 2 * radius_ };
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::move(const point_t & newPoint)
{
  center_ = newPoint;
}
