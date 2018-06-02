#include "rectangle.hpp"

#include <iostream>

Rectangle::Rectangle(const rectangle_t & rect):
  rect_(rect)
{
  if( (rect_.height < 0.0) || (rect_.width < 0.0) )
  {
    std::cerr << "Error. incorrect height or width" << std::endl;
  }
}

double Rectangle::getArea() const
{
  return (rect_.width * rect_.height);
}

rectangle_t Rectangle::getFrameRect() const
{
  return rect_;
}

void Rectangle::move(const double dx, const double dy)
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
}

void Rectangle::move(const point_t & pos)
{
  rect_.pos = pos;
}
