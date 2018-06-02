#include <cassert>
#include <iostream>
#include "rectangle.hpp"

Rectangle::Rectangle(const rectangle_t& parameters) :  parameters_(parameters)
{
  assert (parameters.width >= 0.0 && parameters.height >= 0.0);
}

double Rectangle::getArea () const
{
  return parameters_.width * parameters_.height;
}

rectangle_t Rectangle::getFrameRect() const
{
  return parameters_;
}

void Rectangle::move(double dx, double dy)
{
  parameters_.pos.x += dx;
  parameters_.pos.y += dy;
}

void Rectangle::move(const point_t& pos)
{
  parameters_.pos = pos;
}
