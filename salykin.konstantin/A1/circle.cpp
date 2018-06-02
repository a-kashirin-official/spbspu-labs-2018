#include <iostream>
#include <cmath>

#include "circle.hpp"

Circle::Circle(double radius, const point_t& center):
  center_(center),
  radius_(radius)
{
  if (radius_ < 0.0) {
    throw std::invalid_argument("Radius cannot be < 0.0");
  }
}

double Circle::getArea() const
{
  return(M_PI * radius_ * radius_);
}

rectangle_t Circle::getFrameRect() const
{
  return { 2 * radius_, 2 * radius_, center_ };
}

void Circle::move(const point_t& newPos)
{
  center_ = newPos;
}

void Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}
