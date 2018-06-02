#include "circle.hpp"
#include <cmath>
#include <iostream>

brusnitsyna::Circle::Circle(const point_t & center, double radius):
  center_(center),
  radius_(radius)
{
  if (radius < 0.0) {
    throw std::invalid_argument("Invalid radius");
  }
}

double brusnitsyna::Circle::getArea() const
{
  return pow(radius_, 2) * M_PI;
}

brusnitsyna::rectangle_t brusnitsyna::Circle::getFrameRect() const
{
  return {2 * radius_, 2 * radius_, center_};
}

void brusnitsyna::Circle::move(const point_t & pos)
{
  center_ = pos;
}

void brusnitsyna::Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void brusnitsyna::Circle::scale(double k)
{
  if (k < 0.0) {
    throw std::invalid_argument("Invalid k");
  }
  radius_ *= k;
}
