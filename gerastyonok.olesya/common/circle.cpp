#include "circle.hpp"
#include <iostream>
#define _USE_MATH_DEFINES 
#include <math.h> 

using namespace gerastyonok;

gerastyonok::Circle::Circle(double r, const point_t & center) :
  rad_(r),
  center_(center)
{
  if (rad_ < 0.0)
  {
    throw std::invalid_argument("Error!");

  }
}


double gerastyonok::Circle::getArea() const
{
  return rad_ * rad_ * M_PI;
}

rectangle_t gerastyonok::Circle::getFrameRect() const
{
  return {2 * rad_, 2 * rad_, center_ };
}

void gerastyonok::Circle::move(const point_t & pos)
{
  center_ = pos;
}

void gerastyonok::Circle::move(double px, double py)
{
  center_.x += px;
  center_.y += py;
}

void gerastyonok::Circle::scale(const double k)
{
  if (k < 0.0)
    {
   
    throw std::invalid_argument("Error!");

    }
 
  rad_ = rad_ * k;
}

point_t gerastyonok::Circle::getCenter() const
{
  return center_;
}

