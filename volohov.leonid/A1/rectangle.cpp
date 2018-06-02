#include <cassert>
#include "rectangle.hpp"

Rectangle::Rectangle(const point_t & center, const double width, const double height):
  center_(center),
  width_(width),
  height_(height)
{
  assert((width >= 0.0) || (height >= 0.0));
};

double Rectangle::getArea() const
{
  return width_ * height_;
};

rectangle_t Rectangle::getFrameRect() const
{
  return {center_, width_, height_};
};

void Rectangle::move(const point_t & newCenter)
{
  center_ = newCenter;
};

void Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
};
