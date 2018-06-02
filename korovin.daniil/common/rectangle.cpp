#include <cmath>
#include <iostream>
#include "rectangle.hpp"
using namespace korovin;
Rectangle::Rectangle(const point_t & rectCenter,const double width,const double height):
  rectCenter_(rectCenter),
  width_(width),
  height_(height)
{
  if ((width_ < 0.0) || (height_ < 0.0))
  {
    throw std::invalid_argument("Invalid rectangle height or width.");
  }
}


double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {rectCenter_, width_, height_};
}

void Rectangle::move(const point_t & newPoint)
{
  rectCenter_ = newPoint;
}

void Rectangle::move(const double dx, const double dy)
{
  rectCenter_.x += dx;
  rectCenter_.y += dy;
}

point_t Rectangle::getPos() const 
{
  return getFrameRect().pos;
}

void Rectangle::scale(const double coefficient)
{
  if (coefficient < 0.0)
  {
    throw std::invalid_argument("Invalid scale coefficient.");
  }
  else
  {
    width_ *= coefficient;
    height_ *= coefficient;
  }
}
