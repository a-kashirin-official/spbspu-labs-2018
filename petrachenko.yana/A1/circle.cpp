#include "circle.hpp"
#include <cmath>
#include <iostream>

Circle::Circle(const double radius, const point_t &center):
  radius_(radius),
  center_(center)
{
  if (radius < 0.0)
  {
    std::cerr << "Invalid_circle_radius" << std::endl;
  }
}

double Circle::getArea() const
{
  return M_PI * pow(radius_, 2);
}

rectangle_t Circle::getFrameRect() const
{
  return { 2 * radius_, 2 * radius_, center_};
}

void Circle::move(const point_t &p)
{
  center_ = p;
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

