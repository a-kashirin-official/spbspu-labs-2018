#include "rectangle.hpp"

#include <iostream>

Rectangle::Rectangle(double w, double h, const point_t & p):
  width_(w),
  height_(h),
  pos_(p)
{
  if (width_ <= 0)
  {
    std::cerr << "Invalid_rectangle_width";
  }
  if (height_ <= 0)
  {
    std::cerr << "Invalid_rectangle_heigth";
  }
}

double Rectangle::getArea() const
{
  return height_ * width_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {width_, height_, pos_};
}

void Rectangle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Rectangle::move(const point_t & p)
{
  pos_ = p;
}

void Rectangle::printParameters()const
{
  std::cout << "Rectangle width=" << width_ << std::endl;
  std::cout << "Rectangle height=" << height_ << std::endl;
  std::cout << "Rectangle center (" << pos_.x << "," << pos_.y << ")" << std::endl;
}

void Rectangle::printCenter() const
{
  std::cout << " (" << pos_.x << "," << pos_.y << ")" << std::endl;
}
