#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

Circle:: Circle(double radius, const point_t& cir):
  radius_(radius),cir_(cir)
{
  if(radius < 0)
  {
    throw std:: invalid_argument("Wrong parametrs");
  }
}
double Circle::getArea() const
{
  return radius_ *radius_*M_PI;
}
rectangle_t Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2,cir_.x, cir_.y, };
}
void Circle::move(double dx,double dy)
{
  cir_.x += dx;
  cir_.y += dy;
}
void Circle::move(const point_t& center)
{
  cir_ = center;
}
