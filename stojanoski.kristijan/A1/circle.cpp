#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdexcept>

Circle::Circle(const point_t & centar, double radius) :
  centar_(centar),
  radius_(radius)
{
  if (radius_ < 0)
  {
    throw std::invalid_argument("invalid circle parameters!");
  }
}
double Circle::getArea() const
{
  return radius_ * radius_*M_PI;
}
rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{ centar_, radius_ * 2,radius_ * 2 };
}
void Circle::move(double dx, double dy)
{
  centar_.x += dx;
  centar_.y += dy;
}
void Circle::move(const point_t & p)
{
  centar_ = p;
}
