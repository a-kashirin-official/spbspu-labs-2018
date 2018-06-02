#include "rectangle.hpp"

#include <iostream>

Rectangle::Rectangle(const point_t & center, const double width, const double height):
  center_(center),
  width_(width),
  height_(height)


{
  if (width < 0) 
  {
    std::cerr << "Invalid_rectangle_width" << std::endl;
  }
  if (height < 0) 
  {
    std::cerr << "Invalid_rectangle_height" << std::endl;
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

void Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Rectangle::move(const point_t & newPoint)
{
  center_ = newPoint;
}
