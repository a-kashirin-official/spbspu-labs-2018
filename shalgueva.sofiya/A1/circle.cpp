#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

Circle::Circle(const point_t & pos, const double radius) :
  position_(pos),
  radius_(radius)
{
  if (radius_ < 0.0)
  {
    std::cerr << "Invalid argument " << std::endl;
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, position_};
}

void Circle::move(double dx, double dy)
{
  position_.x += dx;
  position_.y += dy;
}

void Circle::move(const point_t & posTo)
{
  position_ = posTo;
}
