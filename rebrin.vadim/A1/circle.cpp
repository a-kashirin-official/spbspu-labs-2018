#include <cassert>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "circle.hpp"

Circle::Circle(const point_t& pos, double rad) : center_(pos), radius_(rad)
{
  assert (rad >= 0.0);
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  rectangle_t tmp{};
  tmp.pos.x = center_.x;
  tmp.pos.y = center_.y;
  tmp.width = 2 * radius_;
  tmp.height = 2 * radius_;
  return tmp;
}

void Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::move(const point_t& pos)
{
  center_ = pos;
}
