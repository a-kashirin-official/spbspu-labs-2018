#include <iostream>
#include <assert.h>
#include "rectangle.hpp"

Rectangle::Rectangle(const point_t &pos, double w, double h):
  width_(w),
  height_(h),
  point_(pos)
{
  assert (width_ > 0.0 && height_ > 0.0);
}

double Rectangle::getArea() const
{
  return height_ * width_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {point_, width_, height_};
}

void Rectangle::move(const point_t &pos)
{
  point_ = pos;
}

void Rectangle::move(const double dx, const double dy)
{
  point_.x += dx;
  point_.y += dy;
}
