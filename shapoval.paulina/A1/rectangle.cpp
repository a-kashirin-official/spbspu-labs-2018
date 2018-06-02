#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const point_t & centre, const double width, const double height):
  centre_(centre),
  width_(width),
  height_(height)
{
  if ((width_ < 0) || (height_ < 0))
  {
    throw std::invalid_argument("Invalid rectangle!!");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {centre_, width_, height_};
}

void Rectangle::move(const point_t & new_centre)
{
  centre_ = new_centre;
}

void Rectangle::move(const double dx, const double dy)
{
  centre_.x += dx;
  centre_.y += dy;
}
