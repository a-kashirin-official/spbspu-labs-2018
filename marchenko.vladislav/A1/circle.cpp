#include "circle.hpp"

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

Circle::Circle(const point_t &centerPos, const double radius) :
  center_(centerPos),
  radius_(radius)
{
  if (radius_ < 0.0)
  {
    std::cerr << "Invalid value of radius" << std::endl;
  }
}

double Circle::getArea() const
{
  return radius_ * radius_ * M_PI;
}

rectangle_t Circle::getFrameRect() const
{
  return { radius_ * 2, radius_ * 2, center_ };
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::move(const point_t &newPos)
{
  center_ = newPos;
}
