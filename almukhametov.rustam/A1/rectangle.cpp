#include "rectangle.hpp"
#include <iostream>
#include <cassert>

Rectangle::Rectangle(double h, double w, point_t c):
  height_(h),
  width_(w),
  center_(c)
{
  assert(h>=0 and w>=0);
}

double Rectangle::getArea() const
{
  return height_*width_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {width_,height_,center_};
}

void Rectangle::move(point_t c)
{
  center_ = c;
}

void Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}
