#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const rectangle_t & rctng):
rec(rctng)
{
  if (rctng.height <= 0)
  {
    throw std::invalid_argument("Height must be > 0");
  }
  if (rctng.width <= 0)
  {
    throw std::invalid_argument("Width must be > 0");	
  }
}

double Rectangle::getArea() const noexcept
{
  return rec.width* rec.height;
}

rectangle_t Rectangle::getFrameRect() const noexcept
{
  return rec;
}

void Rectangle::move(const point_t & point) noexcept
{
  rec.pos = point;
}

void Rectangle::move(const double dx, const double dy) noexcept
{
  rec.pos.x += dx;
  rec.pos.y += dy;
}
