#include <stdexcept>
#include <iostream>
#include <cmath>
#include "circle.hpp"

revtova::Circle::Circle(const point_t & pos, const double radius):
  pos_(pos),
  radius_(radius),
  angle_(0.0)
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
void revtova::Circle::scale(const double kscale)
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
void revtova::Circle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}
void revtova::Circle::rotate(const double angle)
{
  angle_ += angle;
  if (angle_ >= 360)
  {
    angle_ = fmod(angle_, 360.0);
  }
}
