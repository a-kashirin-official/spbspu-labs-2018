#include "circle.hpp"
#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>

using namespace aknazarova;

Circle::Circle(const point_t &pos, const double rad) :
  point_(pos),
  radius_(rad)
{
  if (rad<=0)
  {
    throw std::invalid_argument("invalid argument circle");
  }
}

double Circle::getArea()const
{
  return radius_*radius_*M_PI;
}

rectangle_t Circle::getFrameRect() const
{
  return {point_,radius_*2,radius_*2};
}

void Circle::scale(double kof)
{
  if (kof<0)
  {
   throw std::invalid_argument("invalid Kof!");
  }
  else
  {
    radius_=radius_*kof;
  }
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
