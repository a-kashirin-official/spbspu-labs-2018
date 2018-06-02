#include <iostream>
#include <cmath>

#include "circle.hpp"

pristup::Circle::Circle(double radius, const point_t & position):
  r_(radius),
  p_(position)
{
  if (r_ < 0.0)
  {
    throw std::invalid_argument("it is not right radius");
  }
}

double pristup::Circle::getArea() const noexcept
{
  return (M_PI * r_ * r_);
}

pristup::rectangle_t pristup::Circle::getFrameRect() const noexcept
{
  return rectangle_t{2 * r_, 2 * r_, p_};
}

void pristup::Circle::move(const point_t & p) noexcept
{
  p_ = p;
}

void pristup::Circle::move(double dx, double dy) noexcept
{
  p_.x += dx;
  p_.y += dy;
}

void pristup::Circle::scale(double k)
{
    if (k < 0.0)
    {
        throw std::invalid_argument("it is not right parameter of scaling");
    }
    r_ *= k;
}

