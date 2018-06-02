#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const double width, const double height, const point_t &centerPos) :
  width_(width),
  height_(height),
  center_(centerPos)
{
  if (width_ < 0.0)
  {
    std::cerr << "Invalid value of width" << std::endl;
  }
  if (height_ < 0.0)
  {
    std::cerr << "Invalid value of height" << std::endl;
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return { width_ , height_ , center_ };
}

void Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Rectangle::move(const point_t &newPos)
{
  center_ = newPos;
}
