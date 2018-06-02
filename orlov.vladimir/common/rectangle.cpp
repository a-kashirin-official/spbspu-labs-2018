#include "rectangle.hpp"
#include <stdexcept>

using namespace orlov;

orlov::Rectangle::Rectangle(const rectangle_t & rctng):
rec_(rctng)
{
  if (rctng.height <= 0.0)
  {
    throw std::invalid_argument("Height must be > 0");
  }
  if (rctng.width <= 0.0)
  {
    throw std::invalid_argument("Width must be > 0");
  }
}

double orlov::Rectangle::getArea() const noexcept
{
  return (rec_.width * rec_.height);
}

point_t orlov::Rectangle::getPos() const noexcept
{
  return rec_.pos;
}

rectangle_t orlov::Rectangle::getFrameRect() const noexcept
{
  return rec_;
}

void orlov::Rectangle::move(const point_t & point) noexcept
{
  rec_.pos = point;
}

void orlov::Rectangle::move(const double dx, const double dy) noexcept
{
  rec_.pos.x += dx;
  rec_.pos.y += dy;
}

void orlov::Rectangle::scale(const double koef)
{
  if (koef <= 0.0)
  {
    throw std::invalid_argument("Koef must be > 0");
  }

  rec_.height *= koef;
  rec_.width *= koef;
}
