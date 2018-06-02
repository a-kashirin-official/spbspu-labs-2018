#include <iostream>

#include "rectangle.hpp"

Rectangle::Rectangle(double width, double height, const point_t& center):
  center_(center),
  width_(width),
  height_(height)
{
  if ((width_ < 0.0) || (height_ < 0.0)) {
    throw std::invalid_argument("Width and height cannot be < 0.0");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return { width_, height_, center_ };
}

void Rectangle::move(const point_t& newPos)
{
  center_ = newPos;
}

void Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}
