#include <cmath>
#include <cassert>
#include "circle.hpp"

Circle::Circle(const point_t & center,const double radius):
  center_(center),
  radius_(radius)
{
  assert( radius > 0.0);
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{center_, 2*radius_, 2*radius_};
}

void Circle::move(const point_t & newCenter)
{
  center_ = newCenter;
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}
