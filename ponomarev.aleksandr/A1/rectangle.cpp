#include "rectangle.hpp"
#include <cassert>

Rectangle::Rectangle(const point_t &center, const double width, const double height):
  position_(center),
  width_(width),
  height_(height)
{
  assert(width >= 0 && height >= 0);
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_t{width_, height_, position_};
}

void Rectangle::move(const point_t &center)
{
  position_ = center;
}

void Rectangle::move(const double dx, const double dy)
{
  position_.x += dx;
  position_.y += dy;
}
