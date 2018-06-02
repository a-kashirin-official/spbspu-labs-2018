#include <cassert>
#include "rectangle.hpp"

Rectangle::Rectangle(const double height, const double width, const point_t & center):
  height_(height),
  width_(width),
  center_(center)
{
  assert ((height >= 0.0) && (width >= 0.0));
}

double Rectangle::getArea() const
{
  return height_ * width_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {center_,width_,height_};
}

void Rectangle::move(const point_t & newLocation)
{
  center_ = newLocation;
}

void Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}
