#include <iostream>
#include <cmath>

#include "circle.hpp"

salykin::Circle::Circle(const double radius, const salykin::point_t & center):
  center_(center),
  radius_(radius)
{
  if (radius_ < 0.0) {
    throw std::invalid_argument("Invalid radius");
  }
}

double salykin::Circle::getArea() const
{
  return (M_PI * radius_ * radius_);
}

salykin::rectangle_t salykin::Circle::getFrameRect() const
{
  return {2 * radius_, 2 * radius_, center_};
}

void salykin::Circle::move(const salykin::point_t & newPos)
{
  center_ = newPos;
}

void salykin::Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

salykin::point_t salykin::Circle::getPos() const
{
  return center_;
}

void salykin::Circle::scale(const double multiplier)
{
  if (multiplier < 0.0)
  {
    throw std::invalid_argument("Invalid multiplier");
  }
  radius_ *= multiplier;
}

double salykin::Circle::getRadius() const
{
  return radius_;
}
