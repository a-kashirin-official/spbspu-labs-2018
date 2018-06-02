#include "rectangle.hpp"
#include <stdexcept>
#include <iostream>

Rectangle::Rectangle(const point_t &center, double width, double height) :
  rectangle_({ center, width, height })
{
  if(width <= 0.0 || height <= 0.0)
  {
    throw std::invalid_argument("Invalid Rectangle parameters!");
  }
}
double Rectangle::getArea() const
{
  return rectangle_.width * rectangle_.height;
}
rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_;
}
void Rectangle::move(double dx, double dy)
{
  rectangle_.pos.x += dx;
  rectangle_.pos.y += dy;
}
void Rectangle::move(const point_t &p)
{
  rectangle_.pos = p;
}

