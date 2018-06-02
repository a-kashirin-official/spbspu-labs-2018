#include "circle.hpp"
#include <iostream>
#include <stdexcept>

const double M_PI = 3.141592653589793238463;

revtova::Circle::Circle(const point_t & pos, const double radius):
  pos_(pos),
  radius_(radius)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Invalid value");
  }
}
double revtova::Circle::getArea() const
{
  return (M_PI*radius_*radius_);
}
revtova::rectangle_t revtova::Circle::getFrameRect() const
{
  return {radius_*2, radius_*2, pos_};
}
void revtova::Circle::scale(double kscale)
{
if (kscale < 0.0)
  {
    throw std::invalid_argument("Invalid value");
  }
  radius_ *= kscale;
}
void revtova::Circle::move(const point_t & pos)
{
  pos_ = pos;
}
void revtova::Circle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}
