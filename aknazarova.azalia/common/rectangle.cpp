#include <iostream>

#include "rectangle.hpp"

using namespace aknazarova;
Rectangle::Rectangle(const point_t &pos, double w, double h):
  width_(w),
  height_(h),
  point_(pos)
{
  if ((height_<=0.0)||(width_<=0.0))
  {
    throw std::invalid_argument("Invalid argument rectangle");
  }
}

double Rectangle::getArea() const
{
  return height_ * width_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {point_, width_, height_};
}
  
void Rectangle::scale(double kof)
{
  if (kof<0)
  {
    throw std::invalid_argument("Invalid kof");
  }
  else
  {
    height_=height_*kof;
    width_=width_*kof;
  }
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
