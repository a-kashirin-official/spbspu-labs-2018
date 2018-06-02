#include "circle.hpp"
#include <cmath>
#include <cassert>

Circle::Circle(double r, point_t c):
  radius_(r),
  center_(c)
{
  assert(r>=0);
}

double Circle::getArea() const
{
  return M_PI*radius_*radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return{2*radius_, 2*radius_, center_};
}

void Circle::move(point_t c)
{
  center_ = c;
}

void Circle::move(double dx, double dy)
{
  center_.y += dy;
  center_.x += dx;
}
