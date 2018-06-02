#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const double width, const double height, const point_t &center):
  width_(width),
  height_(height),
  center_(center)
{
  if (width < 0.0){
    std::cerr << "Invalid_rectangle_width" << std::endl;
  }
  if (height < 0.0){
    std::cerr << "Invalid_rectangle_height" << std::endl;
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {width_, height_, center_};
}

void Rectangle::move(const point_t &p)
{
  center_ = p;
}

void Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

