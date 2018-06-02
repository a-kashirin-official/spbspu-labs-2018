#include "circle.hpp"
#include <iostream>
#include <cmath>

Circle::Circle(const point_t & centre, const double radius):
  centre_(centre),
  radius_(radius)
{
  if (radius < 0)
  {
    throw std::invalid_argument("Wrong RADIUS!");
  }
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{(radius_ * 2), (radius_ * 2), centre_};
}

double Circle::getArea() const
{
  return (M_PI * radius_ * radius_);
}

void Circle::move(const point_t &newCentrePoint)
{
  centre_ = newCentrePoint;
}

void Circle::move(const double dx, const double dy)
{
  centre_.x += dx;
  centre_.y += dy;
}
