#include "circle.hpp"
#include <iostream>
#include <cassert>
#include <math.h>

Circle::Circle(const point_t &pos, const double rad) :
  pos_(pos),
  radius_(rad)
{
  assert(radius_ >= 0.0);
}

void Circle::move(const point_t &pos)
{
  pos_ = pos;
}

void Circle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

double Circle::getArea() const
{
  return radius_ * radius_ * M_PI;
}

rectangle_t Circle::getFrameRect() const
{
  return {pos_, 2 * radius_, 2 * radius_};
}

void Circle::printInfo() const
{
  std::cout << "center = (" << pos_.x << ", " << pos_.y << ")" << std::endl
    << "radius = " << radius_ << std::endl;
}
