#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const double width,const double height, const point_t &pos):
  width_(width),
  height_(height),
  center_(pos)
{
  if (width <= 0 || height <= 0)
  {
    throw std::invalid_argument("Invalid argument");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {width_, height_, center_};
}

void Rectangle::move(const point_t &point)
{
  center_ = point;
}

void Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}
