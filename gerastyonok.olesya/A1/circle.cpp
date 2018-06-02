#include "circle.hpp"
#include <iostream>
#define _USE_MATH_DEFINES 
#include <math.h> 

Circle::Circle(double r, const point_t & center) :
  rad_(r),
  center_(center)
{
  if (rad_ < 0)
  {
    std::cerr << "Invalid radius" << std::endl;
  }
}


double Circle::getArea() const
{
  return rad_ * rad_ * M_PI;
}

rectangle_t Circle::getFrameRect() const
{
  return {2 * rad_, 2 * rad_, center };
}

void Circle::move(const point_t & pos)
{
  center = pos;
}

void Circle::move(double px, double py)
{
  center.x = center.x + px;
  center.y = center.y + py;
}
