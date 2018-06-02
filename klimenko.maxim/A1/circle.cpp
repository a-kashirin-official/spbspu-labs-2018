#include "circle.hpp"
#include <stdexcept>
#include <math.h>

Circle::Circle(const double r, const point_t & point):
centre_(point),
radius_(r)
{
  if (r <= 0)
  {
    std::invalid_argument("Invalid radius");
  }
}

double Circle::getArea() const noexcept
{
  return (M_PI * radius_ * radius_);
}

rectangle_t Circle::getFrameRect() const noexcept
{
  return rectangle_t({ (radius_ * 2.0), (radius_ * 2.0), { centre_.x, centre_.y } });
}

void Circle::move(const point_t & point) noexcept
{
  centre_ = point;
}

void Circle::move(const double dx, const double dy) noexcept
{
  centre_.x += dx;
  centre_.y += dy;
}
