#include "circle.hpp"
#include <iostream>
#include <math.h>

Circle::Circle(const double radius, const point_t & point):
cpoint(point),
r(radius)
{
  if (r <= 0)
  {
    throw std::invalid_argument("Radius must be > 0");
  }
}

double Circle::getArea() const noexcept
{
  return M_PI * pow(r, 2);
}

rectangle_t Circle::getFrameRect() const noexcept
{
  return rectangle_t({ (r * 2.0), (r * 2.0), { cpoint.x, cpoint.y } });
}

void Circle::move(const point_t & point) noexcept
{
  cpoint = point;
}

void Circle::move(const double dx, const double dy) noexcept
{
  cpoint.x += dx;
  cpoint.y += dy;
}
