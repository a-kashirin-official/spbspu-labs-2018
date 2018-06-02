#include "rectangle.hpp"
#include <iostream>


Rectangle::Rectangle(const point_t & center, const double w, const double h):
  pos_(center),
  width_(w),
  height_(h)
{
  if (width_ <= 0)
  {
    std::cerr << "Invalid rectangle's width" << std::endl;
  }
  if (height_ <= 0)
  {
    std::cerr << "Invalid rectangle's height" << std::endl;
  }
}

void Rectangle::output() const
{
  std::cout << "Coordinates of rectangle center (" << pos_.x << "," << pos_.y << ")" << std::endl;
}

void Rectangle::move(const point_t & pos)
{
  pos_ = pos;
}

void Rectangle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {width_, height_, pos_};
}
