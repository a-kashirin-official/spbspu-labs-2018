#include "circle.hpp"
#include <cmath>
#include <iostream>

Circle::Circle(const point_t & center, double radius):
  center_(center),
  radius_(radius)
{
  if (radius < 0) {
    std::cerr << "Invalid radius" << std::endl;
  }
}

double Circle::getArea() const
{
  return pow(radius_, 2) * M_PI;
}

rectangle_t Circle::getFrameRect() const
{
  return {2 * radius_, 2 * radius_, center_};
}

void Circle::move(const point_t & pos)
{
  center_ = pos;
}

void Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}
