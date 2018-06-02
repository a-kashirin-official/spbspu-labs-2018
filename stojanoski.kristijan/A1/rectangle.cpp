#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const point_t & centar, double height, double width) :
  rect_({ centar, height, width })
{
  if (height < 0 || width < 0) 
  {
    throw std::invalid_argument("Invalid Rectangle parameters!");
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
void Rectangle::move(double dx, double dy)
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
}
void Rectangle::move(const point_t & p)
{
  rect_.pos = p;
}
