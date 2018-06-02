#include "rectangle.hpp"
#include <iostream>
#include <cassert>

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
  rectangle_t rectangle;
  rectangle.pos.x = point_.x;
  rectangle.pos.y = point_.y;
  rectangle.width = width_;
  rectangle.height = height_;
  return rectangle;
}

void Rectangle::move(const point_t &pos)
{
  point_ = pos;
}

void Rectangle::move(double dx, double dy)
{
  point_.x +=dx;
  point_.y +=dy;
}
