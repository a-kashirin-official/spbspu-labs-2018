#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include  <stdexcept>


reznik::Circle:: Circle(double radius, const reznik::point_t& cir):
  radius_(radius),
  cir_(cir)
{
  if(radius < 0)
  {
    throw std:: invalid_argument("Wrong parametrs");
  }
}
double reznik::Circle::getArea() const
{
  return radius_ *radius_*M_PI;
}
reznik::rectangle_t reznik::Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2,cir_.x, cir_.y, };
}
void reznik::Circle::move(double dx,double dy)
{
  cir_.x += dx;
  cir_.y += dy;
}
void reznik::Circle::move(const point_t& center)
{
  cir_ = center;
}

void reznik::Circle::scale(double k)
{
  if (k < 0)
  {
    throw std:: invalid_argument("Wrong parametrs");
  }
  else
  {
    radius_ *= k;
  }
}
