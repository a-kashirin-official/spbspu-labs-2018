#include <cassert>
#include <cmath>
#include "rectangle.hpp"

Rectangle::Rectangle(const point_t & angle,const double width,const double heigth):
  angle_(angle),
  width_(width),
  heigth_(heigth)
{
  assert((width >= 0.0) && (heigth >= 0.0));
}

double Rectangle::getArea() const
{
  return width_ * heigth_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {angle_, width_, heigth_};
}

void Rectangle::move(const point_t & newPoint)
{
  angle_ = newPoint;
}

void Rectangle::move(const double dx, const double dy)
{
  angle_.x += dx;
  angle_.y += dy;
}
