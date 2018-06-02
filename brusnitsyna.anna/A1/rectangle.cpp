#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const rectangle_t & rect):
  rect_(rect)
{
  if (rect.width < 0 || rect.height < 0) {
    std::cerr << "Invalid rectangle height or width" << std::endl;
  }
}

double Rectangle::getArea() const
{
  return rect_.width * rect_.height;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rect_;
}

void Rectangle::move(const point_t & pos)
{
  rect_.pos = pos;
}

void Rectangle::move(double dx, double dy)
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
}
