#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const rectangle_t & rctng):
rec_(rctng)
{
  if (rctng.height <= 0)
  {
    std::invalid_argument("Invalid rectangle width");
  }
  if (rctng.width <= 0)
  {
    std::invalid_argument("Invalid rectangle width");
  }
}

double Rectangle::getArea() const noexcept
{
  return rec_.width * rec_.height;
}

rectangle_t Rectangle::getFrameRect() const noexcept
{
  return rec_;
}

void Rectangle::move(const point_t & point) noexcept
{
  rec_.pos = point;
}

void Rectangle::move(const double dx, const double dy) noexcept
{
  rec_.pos.x += dx;
  rec_.pos.y += dy;
}
