#include "rectangle.hpp"

#include <iostream>

Rectangle::Rectangle(const double height, const double width, const point_t & middle):
  middle_(middle),
  height_(height),
  width_(width)
{
  if (height_ < 0.0)
  {
    throw std::invalid_argument("Incorrect height value");
  }
  if (width_ < 0.0)
  {
    throw std::invalid_argument("Incorrect width value");
  }
}

double Rectangle::getArea() const
{
  return height_ * width_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {height_, width_, middle_};
}

void Rectangle::move(const point_t & newPosition)
{
  middle_ = newPosition;
}

void Rectangle::move(const double dx, const double dy)
{
  middle_.x += dx;
  middle_.y += dy;
}
