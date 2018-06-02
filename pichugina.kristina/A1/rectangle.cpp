#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const point_t & pos, double w, double h):
 width_(w),
 height_(h),
 point_(pos)
{
  if (width_ <= 0.00)
  {
    std::cerr << "Invalid rectangle width" << std::endl;
  }
  if (height_ <= 0.00)
  {
    std::cerr << "Invalid rectangle height" << std::endl;
  }
}

double Rectangle::getArea() const
{
  return height_ * width_;
}

rectangle_t Rectangle::getFrameRect() const
{
  rectangle_t rectangle;
  rectangle.pos.x = point_.x;
  rectangle.pos.y = point_.y;
  rectangle.width = width_;
  rectangle.height = height_;
  return rectangle;
}

void Rectangle::move(const point_t & pos)
{
  point_ = pos;
}

void Rectangle::move(double dx, double dy)
{
  point_.x +=dx; 
  point_.y +=dy; 
}
