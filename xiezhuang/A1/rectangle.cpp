#include "rectangle.hpp"
#include <iostream>
#include <cassert>

Rectangle::Rectangle(const point_t &pos, const double width, const double height):
  pos_(pos),
  width_(width),
  height_(height)
{
  assert(width_ >= 0.0 && height_ >= 0.0);
}

void Rectangle::move(const point_t &pos)
{
  pos_ = pos;
}

void Rectangle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {pos_, width_, height_};
}

void Rectangle::printInfo() const
{
  std::cout << "center = (" << pos_.x << ", " << pos_.y << ")" << std::endl
    << "height = " << height_ << " width = " << width_ << std::endl;
}
