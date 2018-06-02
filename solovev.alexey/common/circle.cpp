#include <iostream>
#include <stdexcept>
#include <cmath>
#include "circle.hpp"

using namespace solovev;

Circle::Circle(double rad, point_t pos):
  rad_(rad),
  center_(pos)
{
  if (rad<0.0)
  {
    throw std::invalid_argument("Radius must be>=0");
  }
}

double Circle::getArea() const
{
  return (M_PI * rad_ * rad_);
}

rectangle_t Circle::getFrameRect() const
{
  return {2*rad_, 2*rad_, center_};
}

void Circle::move (point_t pos)
{
  center_ = pos;
}

void Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::scale(double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Factor is less than 0");
  }
  else rad_ *= factor;
}
