#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <assert.h>
#include <math.h>
#include <iostream>

Circle::Circle(const point_t &pos, const double rad) :
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
  return {point_,radius_*2,radius_*2};
}

void Circle::move(const point_t &pos)
{
  point_ = pos;
}

void Circle::move(const double dx, const double dy)
{
  point_.x += dx;
  point_.y += dy;
}
