#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>

stakhiev::Rectangle::Rectangle(const stakhiev::point_t & cent, const double w, const double h):
  Rect_{w, h, cent}
{
  if ((w < 0.0) || (h < 0.0))
  {
    throw std::invalid_argument("Incorrect coefficient");
  }
  //Invalid value of width and/or height
}
double stakhiev::Rectangle::getArea() const
{
  return Rect_.width * Rect_.height;
}
stakhiev::rectangle_t stakhiev::Rectangle::getFrameRect() const
{
  return Rect_;
}
void stakhiev::Rectangle::move(const double dx, const double dy)
{
  Rect_.pos.x += dx;
  Rect_.pos.y += dy;
}
void stakhiev::Rectangle::move(const stakhiev::point_t & newCenter)
{
  Rect_.pos = newCenter;
}
void stakhiev::Rectangle::scale(const double increaseCoefficient)
{
  if (increaseCoefficient < 0.0)
  {
    throw std::invalid_argument("Incorrect coefficient");
  }
  //Invalid value of increase coefficient
  Rect_.width *= increaseCoefficient;
  Rect_.height *= increaseCoefficient;
}
