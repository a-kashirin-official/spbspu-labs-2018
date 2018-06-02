#include "circle.hpp"
#include <iostream>
#include <cmath>
#include <cassert>

Circle::Circle(const double radius, const point_t &centr) :
  radius_(radius), centr_(centr)
{
  assert(radius >= 0);
}

double Circle::getArea() const
{
  return radius_ * radius_ * M_PI;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{(radius_ * 2), (radius_ * 2), centr_ };
}

void Circle::move(const point_t &point)
{
  centr_ = point;
}

void Circle::move(const double deltaX, const double deltaY)
{
  centr_.x += deltaX;
  centr_.y += deltaY;
}
