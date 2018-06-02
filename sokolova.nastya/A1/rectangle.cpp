#include "rectangle.hpp"

#include <iostream>
#include <stdexcept>

Rectangle::Rectangle(const point_t &centre, double width, double height) :
  width_(width),
  height_(height)
{
  centre_=centre;
  if (width_  <  0.0) {
    throw std::invalid_argument("Wrong width!");
  }
  if (height_ < 0.0) {
    throw std::invalid_argument("Wrong height!");
  }
}

double Rectangle::getArea() const
{
  return width_*height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {centre_, width_, height_};
}

void Rectangle::move(double dx, double dy)
{
  centre_.x += dx;
  centre_.y += dy;
}

void Rectangle::move(const point_t &newcentre)
{
  centre_ = newcentre;
}

void Rectangle::scale(double factor)
{
  if (factor < 0.0) {
    throw std::invalid_argument("Wrong factor!");
  }
  width_ *= factor;
  height_ *= factor;
}
