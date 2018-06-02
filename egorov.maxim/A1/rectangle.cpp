#include "rectangle.hpp"
#include <iostream>
#include <cassert>

Rectangle::Rectangle(const rectangle_t &rectangle) :
  rectangle_(rectangle)
{
  assert(rectangle_.width >= 0 && rectangle_.height >= 0);
}

double Rectangle::getArea() const
{
  return rectangle_.width * rectangle_.height;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_;
}

void Rectangle::move(const point_t &point)
{
  rectangle_.pos = point;
}

void Rectangle::move(const double deltaX, const double deltaY)
{
  rectangle_.pos.x += deltaX;
  rectangle_.pos.y += deltaY;
}
