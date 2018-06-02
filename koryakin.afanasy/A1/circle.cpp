#include "circle.hpp"
#include <math.h>
#include <stdexcept>

Circle::Circle(const point_t &center, const double radius) :
  center_(center),
  radius_(radius)
{
  if(radius_ < 0.0)
  {
    throw std::invalid_argument("Invalid circle parameters!");
  }
}
double Circle::getArea() const
{
  return radius_*radius_*M_PI;
}
rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{ center_, radius_ * 2, radius_ * 2 };
}
void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}
void Circle::move(const point_t &p)
{
  center_ = p;
}
