#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const point_t &center, const double width, const double height):
  center_(center),
  width_(width),
  height_(height)

{
  if (width < 0.0)
  {
    std::cerr << "Width can't be negative" << std::endl;
    width_ = 0.0;
  }
  if (height < 0.0)
  {
    std::cerr << "Height can't be negative" << std::endl;
    height_ = 0.0;
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return { center_, width_, height_ } ;
}

void Rectangle::move(const point_t &newCenterPoint)
{
  center_ = newCenterPoint;
}

void Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}
