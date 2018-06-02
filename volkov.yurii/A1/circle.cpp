#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <cassert>

Circle::Circle(const point_t &p, double rad):
  point_(p),
  radius_(rad)
{
  assert(rad > 0.0);
}


double Circle::getArea() const
{
  return radius_ * radius_ * M_PI;
}

rectangle_t Circle::getFrameRect() const
{
  rectangle_t rectang;
  rectang.height = 2 * radius_;
  rectang.width = 2 * radius_;
  rectang.pos.x = point_.x;
  rectang.pos.y = point_.y;
  return rectang;
}

void Circle::move(const point_t &p)
{
  point_ = p;
}

void Circle::move(double dx, double dy)
{
  point_.x += dx;
  point_.y += dy;
}
