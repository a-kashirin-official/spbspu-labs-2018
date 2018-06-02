#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const point_t & center, const double h, const double w):
  width_(w),
  height_(h),
  pos_(center)
{
  if ((h < 0.0) || (w < 0.0))
  {
    throw std::invalid_argument("Sides can not be negative!");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_t{width_, height_, pos_};
}

void Rectangle::move(const point_t & newCenter)
{
  pos_ = newCenter;
}

void Rectangle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}
