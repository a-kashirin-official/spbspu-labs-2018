
#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const point_t &centre, const double width, const double height) : centre_(centre), width_(width),
                                                                                       height_(height)
{
  if (width <= 0) {
    std::cerr << "Width is incorrect: " << width << ". Must be positive." << std::endl;
  }
  if (height <= 0) {
    std::cerr << "Height is incorrect: " << height << ". Must be positive." << std::endl;
  }
}

rectangle_t Rectangle::getFrameRect() const
{
  return {centre_, width_, height_};
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

void Rectangle::move(const point_t &a)
{
  centre_ = a;
}

void Rectangle::move(double dx, double dy)
{
  centre_.x += dx;
  centre_.y += dy;
}
