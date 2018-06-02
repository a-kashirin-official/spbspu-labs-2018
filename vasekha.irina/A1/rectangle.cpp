#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const point_t & pos, const double width, const double height):
  pos_(pos),
  width_(width),
  height_(height)
{
  if(width<0.0 || height<0.0)
  {
    throw std::invalid_argument("Invalid width or height");
  }
}

double Rectangle::getArea() const
{
  return width_*height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {pos_, width_, height_};
}

void Rectangle::move(const point_t & point)
{
  pos_=point;
}

void Rectangle::move(const double dx, const double dy)
{
  pos_.x+=dx;
  pos_.y+=dy;
}

void Rectangle::print(std::ostream & out) const
{
  out << "Rectangle: center: (" << pos_.x << "," << pos_.y << "), width = "
    << width_ << ", height = " << height_  << std::endl;
}
