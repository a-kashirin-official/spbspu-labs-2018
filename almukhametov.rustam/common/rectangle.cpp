#include "rectangle.hpp"
#include <stdexcept>

using namespace almukhametov;

Rectangle::Rectangle(double h, double w, point_t c):
  height_(h),
  width_(w),
  center_(c)
{
  if (h < 0.0 or w < 0.0)
  {
    throw std::invalid_argument("Height and width must be >= 0");
  }
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

void Rectangle::scale(double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Factor must be >= 0");
  }
  height_ *= factor;
  width_ *= factor;
}
