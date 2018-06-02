#include "rectangle.hpp"

#include <iostream>
#include <stdexcept>

using namespace ivanov;

Rectangle::Rectangle(const rectangle_t & rectangle):
  rectangle_(rectangle)
{
  if ((rectangle_.width < 0.0) || (rectangle_.height < 0.0))
  {
    throw std::invalid_argument ("Wrong WIDTH or HEIGHT!");
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

void Rectangle::move(const point_t &newCentrePoint)
{
  rectangle_.pos = newCentrePoint;
}

void Rectangle::move(const double dx, const double dy)
{
  rectangle_.pos.x += dx;
  rectangle_.pos.y += dy;
}

void Rectangle::scale(const double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("Wrong RATIO!");
  }
  rectangle_.height *= ratio;
  rectangle_.width *= ratio;
}
