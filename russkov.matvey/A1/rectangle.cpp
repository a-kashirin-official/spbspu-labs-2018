//
// Created by russk on 31.03.2018.
//

#include <iostream>
#include <stdexcept>
#include "rectangle.hpp"
#include "base-types.hpp"

Rectangle::Rectangle(point_t &center, double width, double height):
  center_(center),
  width_(width),
  height_(height)
{
  if ((width_ < 0.0) || (height_ < 0.0))
  {
    throw std::invalid_argument("width and height must be non-negative");
  }
}

double Rectangle::getArea() const
{
  return width_*height_ ;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_t{width_, height_, center_};
}

void Rectangle::move(const point_t &point)
{
  center_ = point;
}

void Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Rectangle::scale(const double ratio)
{
  if (ratio <= 0.0)
  {
    throw std::invalid_argument("coefficient should be positive");
  }
  width_ *= ratio;
  height_ *= ratio;
}
