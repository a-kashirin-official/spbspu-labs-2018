#include "rectangle.hpp"

#include <iostream>

Rectangle::Rectangle(const double width, const double height, const point_t & mid):
  mid_(mid),
  width_(width),
  height_(height)
{
  if (width_ < 0.0)
  {
    throw std::invalid_argument("Width must be > 0.0");
  }
  if (height_ < 0.0)
  {
    throw std::invalid_argument("Height must be > 0.0");
  }
}

double Rectangle::getArea() const noexcept
{
  return height_ * width_;
}

rectangle_t Rectangle::getFrameRect() const noexcept
{
  return { width_, height_, mid_ };
}

void Rectangle::move(const point_t & newPos) noexcept
{
  mid_ = newPos;
}

void Rectangle::move(const double dx, const double dy) noexcept
{
  mid_.x += dx;
  mid_.y += dy;
}
