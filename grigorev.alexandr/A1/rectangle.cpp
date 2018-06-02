#include <iostream>
#include "rectangle.hpp"

Rectangle::Rectangle(const point_t & center,const double width,const double heigth):
  center_(center),
  width_(width),
  heigth_(heigth)
{
  if (width < 0.0 || heigth < 0.0)
  {
    throw std::invalid_argument("Error: Invalid width or heigth");
  }
}

double Rectangle::getArea() const
{
  return width_ * heigth_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {center_, width_, heigth_};
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
