#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <cassert>

Circle::Circle(const point_t &pos, double rad) :
  point_(pos),
  radius_(rad)
{
  assert (radius_ > 0.0);
}

double Circle::getArea()const
{
  return radius_*radius_*M_PI;
}

rectangle_t Circle::getFrameRect() const
{
  rectangle_t rectan;
  rectan.height = 2 * radius_;
  rectan.width = 2 * radius_; 
  rectan.pos.x = point_.x; 
  rectan.pos.y = point_.y;
  return rectan;
}

void Circle::move(const point_t &pos)
{
  point_ = pos;
}

void Circle::move(double dx, double dy)
{
  point_.x += dx;
  point_.y += dy;
}

