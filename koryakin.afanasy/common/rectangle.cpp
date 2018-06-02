#include "rectangle.hpp"
#include <iostream>

using namespace koryakin;

Rectangle::Rectangle(const point_t &center, const double width, const double height) :
  rectangle_({ center, width, height })
{
  if(width < 0.0 || height < 0.0)
  {
    throw std::invalid_argument("Invalid Rectangle parameters!");
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
void Rectangle::move(const double dx, const double dy)
{
  rectangle_.pos.x += dx;
  rectangle_.pos.y += dy;
}
void Rectangle::move(const point_t &p)
{
  rectangle_.pos = p;
}

void Rectangle::scale(const double factor)
{
  if (factor >= 0.0) {
    rectangle_.width *= factor;
    rectangle_.height *= factor;
  } else {
    throw std::invalid_argument("The scaling factor must be non-negative");
  }
}
