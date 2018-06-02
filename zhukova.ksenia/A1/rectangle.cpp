#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const point_t & center, const double width, const double height):
  center_(center),
  width_(width),
  height_(height)
{
  if ((width <= 0) || (height <= 0)) {
    std::cerr << "Invalid parameter value" << std::endl;
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_t{ width_, height_, center_ };
}

void Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Rectangle::move(const point_t & point)
{
  center_ = point;
}

void Rectangle::printParameters() const
{
  std::cout << "Rectangle width is " << width_ << ", height is " << height_ << std::endl;
  std::cout << "Rectangle center is in (" << center_.x << ", " << center_.y << ")" << std::endl <<  std::endl;
}
