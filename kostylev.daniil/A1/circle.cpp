#include "circle.hpp"
#include <iostream>
#include <math.h>

Circle::Circle(const point_t & mid, const double radius):
  mid_(mid),
  radius_(radius)
{
  if (radius < 0.0)
  {
    std::cerr << "Invalid radius" << std::endl;
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {mid_, 2 * radius_, 2 * radius_};
}

void Circle::move(const point_t & point)
{
  mid_ = point;
}

void Circle::move(const double dx, const double dy)
{
  mid_.x += dx;
  mid_.y += dy;
}
