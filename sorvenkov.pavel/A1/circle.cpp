#include <cmath>
#include <iostream>

#include "circle.hpp"

Circle::Circle(double radius, const point_t& pos) :
  radius_(radius),
  center_(pos)
{
  if (radius_ < 0.0)
  {
    std::cerr << "Radius must be greater than zero";
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, center_};
}

void Circle::move(const point_t& pos)
{
  center_ = pos;
}

void Circle::move(double Ox, double Oy)
{
  center_.x += Ox;
  center_.y += Oy;
}
