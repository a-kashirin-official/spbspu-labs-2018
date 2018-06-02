#include "rectangle.hpp"

Rectangle::Rectangle(const point_t & center, double height, double width):
  rect_{ center, height, width }
{
  if (height < 0 || width < 0)
  {
    throw IncorrectDataException();
  }
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

double Rectangle::getArea() const
{
  return rect_.height * rect_.width;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rect_;
}
