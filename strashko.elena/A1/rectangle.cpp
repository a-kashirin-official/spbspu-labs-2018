#include "rectangle.hpp"

#include <iostream>

Rectangle::Rectangle(const point_t &centre, double width, double height) :
  width_(width),
  height_(height)
{
  centre_ = centre;
  if (width_ < 0.0) {
    std::cerr << "Invalid_rectangle_width" << std::endl;
    width_ = 0.0;
  }
  if (height_ < 0.0) {
    std::cerr << "Invalid_rectangle_height" << std::endl;
    height_ = 0.0;
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
