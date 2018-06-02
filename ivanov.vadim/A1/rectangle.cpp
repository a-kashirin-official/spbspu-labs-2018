#include "rectangle.hpp"
#include <cmath>
#include <cassert>

Rectangle::Rectangle(const point_t & centr, double height, double width):
  rec_ {centr, height, width}
{
  assert((height >= 0) && (width >= 0));
}

rectangle_t Rectangle::getFrameRect() const
{
  return rec_;
}

double Rectangle::getArea() const
{
  return rec_.height * rec_.width;
}

void Rectangle::move(const point_t & posit)
{
  rec_.pos = posit;
}

void Rectangle::move(double dx, double dy)
{
  rec_.pos.x += dx;
  rec_.pos.y += dy;
}
