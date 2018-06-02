#include <iostream>
#include <stdexcept>
#include "rectangle.hpp"

using namespace solovev;

Rectangle::Rectangle(point_t pos, double width, double height):
  width_(width),
  height_(height),
  center_(pos)
{
  if (height_<0.0)
  {
    throw std::invalid_argument("height must be >=0");
  }
  if (width_<0.0)
  {
    throw std::invalid_argument("width must be >=0");
  }
}

double Rectangle::getArea() const
{
  return (width_ * height_);
}

rectangle_t Rectangle::getFrameRect() const
{
  return {width_, height_, center_};
}

void Rectangle::move(point_t pos)
{
  center_ = pos;
}

void Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Rectangle::scale(double factor)
{
  if (factor >= 0.0)
  {
    width_ *= factor;
    height_ *= factor;
  }
  else throw std::invalid_argument("Factor is less than 0");
}
