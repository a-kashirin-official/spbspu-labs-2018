#include "rectangle.hpp"
#include <cassert>
#include <iostream>

Rectangle::Rectangle(const point_t &point, const double width, const double height):
  pos_(point),
  width_(width),
  height_(height)
{
  assert(width >= 0 && height >= 0);
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  rectangle_t rectangle = {pos_, width_, height_};
  return rectangle;
}

void Rectangle::move(const point_t &point)
{
  pos_ = point;
}

void Rectangle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Rectangle::printInfo() const
{
  std::cout << "Coordinates: (" << pos_.x << "," << pos_.y << ")" << std::endl;
}
