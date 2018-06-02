#include <cassert>
#include <cmath>
#include "rectangle.hpp"

Rectangle::Rectangle(const point_t & rectCenter,const double width,const double heigth):
  rectCenter_(rectCenter),
  width_(width),
  heigth_(heigth)
{
  assert((width > 0.0) || (heigth > 0.0));
}

double Rectangle::getArea() const
{
  return width_ * heigth_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {rectCenter_, width_, heigth_};
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
