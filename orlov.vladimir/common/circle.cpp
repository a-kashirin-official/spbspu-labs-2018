#include "circle.hpp"
#include <stdexcept>

using namespace orlov;

orlov::Circle::Circle(const double r, const point_t & point):
centre_(point),
radius_(r)
{
  if (r <= 0.0)
  {
    throw std::invalid_argument("Radius must be > 0");
  }
}

double orlov::Circle::getArea() const noexcept
{
  return (M_PI * pow(radius_, 2));
}

point_t orlov::Circle::getPos() const noexcept
{
  return centre_;
}

rectangle_t orlov::Circle::getFrameRect() const noexcept
{
  return rectangle_t({ (radius_ * 2.0), (radius_ * 2.0), { centre_.x, centre_.y } });
}

void orlov::Circle::move(const point_t & point) noexcept
{
  centre_ = point;
}

void orlov::Circle::move(const double dx, const double dy) noexcept
{
  centre_.x += dx;
  centre_.y += dy;
}

void orlov::Circle::scale(const double koef)
{
  if (koef <= 0)
  {
    throw std::invalid_argument("Koef must be > 0");
  }

  radius_ *= koef;
}
