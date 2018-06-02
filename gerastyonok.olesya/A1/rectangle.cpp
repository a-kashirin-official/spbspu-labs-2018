#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const rectangle_t & rect) :
  rect_(rect)
{
  if (rect.height < 0.0 || rect.width < 0.0)
  {
    throw std::invalid_argument("Error! Invalid height or width");
  }
}

double Rectangle::getArea() const
{
  return rect_.height * rect_.width;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rect_;
}

void Rectangle::move(const point_t & pos)
{
  center = pos;
}

void Rectangle::move(double px, double py)
{
  center.x = center.x + px;
  center.y = center.y + py;
}
