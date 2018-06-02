#include "rectangle.hpp"
#include <cmath>
#include <cassert>


Rectangle::Rectangle(const point_t & rect,const double width,const double heigth):
  center_(rect),
  width_(width),
  heigth_(heigth)
{
  assert((width >= 0) || (heigth >= 0));
}

double Rectangle::getArea() const
{
  return (width_ * heigth_);
}

rectangle_t Rectangle::getFrameRect() const
{
  return {center_, width_, heigth_};
}

void Rectangle::move(const point_t & center)
{
  center_ = center;
}

void Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}
