#include "circle.hpp"
#include <iostream>
#include <cmath>

Circle::Circle(double radius, const point_t &pos):
  radius_(radius),
  center_(pos)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("Invalid argument");
  }
}

double Circle::getArea() const
{
  return M_PI * pow(radius_, 2);
}

rectangle_t Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, center_};
}

void Circle::move(const point_t &point)
{
  center_ = point;
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}
