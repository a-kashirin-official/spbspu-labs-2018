#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const rectangle_t & rectangle):
  rectangle_(rectangle)
{
  if ((rectangle_.width < 0) || (rectangle_.height < 0))
  {
    throw std::invalid_argument ("Wrong WIDTH or HEIGHT!");
  }
}

double Rectangle::getArea() const
{
  return (rectangle_.width * rectangle_.height);
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_;
}

void Rectangle::move(const point_t &newCentrePoint)
{
  rectangle_.pos = newCentrePoint;
}

void Rectangle::move(double dx, double dy)
{
  rectangle_.pos.x += dx;
  rectangle_.pos.y += dy;
}
