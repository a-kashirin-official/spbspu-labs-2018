#include "circle.hpp"
#include <cmath>
#include <iostream>

Circle::Circle(const point_t & pos, double radius):
  radius_(radius),
  pos_(pos)
{
  if (radius < 0.0)
  {
    std::cerr << "Error. Radius must not be less than 0" << std::endl;
  }
}
double Circle::getArea() const
{
  return radius_*radius_*M_PI;
}
rectangle_t Circle::getFrameRect() const
{
  return{pos_, radius_*2, radius_*2};
}
void Circle::move(const point_t & pos)
{
  pos_=pos;
}
void Circle::move(const double dx, const double dy)
{
  pos_.x+=dx;
  pos_.y+=dy;
}

