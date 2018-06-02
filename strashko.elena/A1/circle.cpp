#include "circle.hpp"

#include <iostream>
#include <cmath>

Circle::Circle(const point_t &centre, double radius) :
  radius_(radius)
{
  centre_ = centre;
  if (radius < 0.0)
  {
    std::cerr << "Invalid_circle" << std::endl;
    radius = 0.0;
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {centre_, 2 * radius_, 2 * radius_ };
}

