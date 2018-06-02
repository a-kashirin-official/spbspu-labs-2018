#include <cassert>
#include <iostream>
#include "rectangle.hpp"

Rectangle::Rectangle(const point_t &position, const double width, const double height):
  pos_(position),
  width_(width),
  height_(height)
{
  assert(width>0 && height>0);
}

void Rectangle::printInformation() const
{
  std::cout << "Coordinates - (" << pos_.x
            << ", " << pos_.y << ")\n";
}
double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {pos_, width_, height_};
}

void Rectangle::move(const point_t &pos)
{
  pos_ = pos;
}

void Rectangle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

