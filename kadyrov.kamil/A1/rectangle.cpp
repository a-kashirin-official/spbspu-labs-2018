#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const rectangle_t &rect) :
  rectangle_(rect)
{
  if (rectangle_.width < 0.0 || rectangle_.height < 0.0)
  {
    std::cerr << "Wrong value of width or height" << std::endl;
  }
}

double Rectangle::getArea() const
{
  return rectangle_.width * rectangle_.height;
}

rectangle_t Rectangle::getFrameRect() const
{
  return { rectangle_.width , rectangle_.height , rectangle_.pos };
}

void Rectangle::move(const double dx, const double dy)
{
  rectangle_.pos.x += dx;
  rectangle_.pos.y += dy;
}

void Rectangle::move(const point_t &newPos)
{
  rectangle_.pos = newPos;
}
