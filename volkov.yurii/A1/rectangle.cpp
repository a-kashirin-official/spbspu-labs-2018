#include "rectangle.hpp"
#include <iostream>
#include <cassert>

Rectangle::Rectangle(const point_t &p, double w, double h):
  width_(w),
  height_(h),
  point_(p)
{
  assert (w > 0.0);
  assert (h > 0.0);
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

void Rectangle::move(const point_t &p)
{
  point_ = p;
}

void Rectangle::move(double dx, double dy)
{
  point_.x +=dx;
  point_.y +=dy;
}
