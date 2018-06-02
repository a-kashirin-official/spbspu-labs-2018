#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const point_t & centre, const double width, const double height):
  centre_(centre),
  width_(width),
  height_(height)
{
  if ((height < 0.0) || (width < 0.0))
  {
    std::cerr << "Invalid height or width" << std::endl;
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

void Rectangle::move(const point_t & point)
{
  centre_ = point;
}

void Rectangle::move(const double dx, const double dy)
{
  centre_.x += dx;
  centre_.y += dy;
}
