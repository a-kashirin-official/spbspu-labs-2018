#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const rectangle_t & rect):
  rect_{rect}
{
  if ((rect_.width < 0.0)||(rect_.height < 0.0))
  {
    std::cerr << "Error. Invalid arguments " << std::endl;
  }
}

double Rectangle::getArea() const
{
  return rect_.width * rect_.height;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {rect_.width, rect_.height, rect_.pos};
}

void Rectangle::move(double dx, const double dy)
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
}

void Rectangle::move(const point_t & posTo)
{
  rect_.pos = posTo;
}
