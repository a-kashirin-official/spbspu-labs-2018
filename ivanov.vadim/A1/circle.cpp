#include "circle.hpp"
#include <cmath>
#include <cassert>

Circle::Circle(const point_t & posit, double radius):
  centr_(posit),
  rad_(radius)
{
  assert(radius >= 0);
}

rectangle_t Circle::getFrameRect() const
{
  return {centr_, rad_ * 2, rad_ * 2};
}

double Circle::getArea() const
{
  return rad_*M_PI*rad_;
}

void Circle::move(const point_t & posit)
{
  centr_ = posit;
}

void Circle::move(double dx, double dy)
{
  centr_.x += dx;
  centr_.y += dy;
}
