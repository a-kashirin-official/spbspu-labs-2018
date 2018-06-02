#include "rectangle.hpp"

#include <iostream>

Rectangle::Rectangle(const point_t & center, const double width, const double height):
  center_(center),
  width_(width),
  height_(height)
{
  if (width_ <= 0)
  {
    std::cerr << "Invalid rectangle width" << std::endl;
  }
  if (height_ <= 0)
  {
    std::cerr << "Invalid rectangle height" << std::endl;
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

double Rectangle::getWidth() const
{
  return width_;
}

double Rectangle::getHeight() const
{
  return height_;
}

point_t Rectangle::getCoordinates() const
{
  return { center_.x, center_.y };
}

rectangle_t Rectangle::getFrameRect() const
{
  return { center_, width_, height_ };
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
