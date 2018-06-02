#include <iostream>
#include "rectangle.hpp"

using namespace volohov;

Rectangle::Rectangle(const point_t & center, const double width, const double height):
  center_(center),
  width_(width),
  height_(height)
{
  if ((width_ < 0.0) || (height_ < 0.0))
  {
    throw std::invalid_argument("Wait. Invalid width or height");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {center_, width_, height_};
}

void Rectangle::scale(const double coeff)
{
  if (coeff < 0.0)
  {
    throw std::invalid_argument("Wait. Invalid coefficient");
  }
  width_ *= coeff;
  height_ *= coeff;
}

void Rectangle::move(const point_t & newCenter)
{
  center_ = newCenter;
}

void Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}
