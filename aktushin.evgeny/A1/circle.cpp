#define _USE_MATH_DEFINES
#include <iostream>
#include <cassert>
#include <cmath>
#include "circle.hpp"

Circle::Circle(const point_t &pos, double radius):
  pos_(pos),
  radius_(radius)
{
  assert(radius >= 0);
}

double Circle::getArea() const
{
  return (radius_ * radius_ * M_PI);
}

rectangle_t Circle::getFrameRect() const
{
  return {pos_, radius_ * 2 , radius_ * 2};
}

void Circle::move(const point_t &pos)
{
  pos_ = pos;
}

void Circle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Circle::printInfo() const
{
  std::cout << "Circle info: ({" << pos_.x << ", " << pos_.y << "}, " << radius_ << ")\n";
}
