#include "circle.hpp"
#include <stdexcept>
#include <cmath>

Circle::Circle(const double radius, const point_t & center):
  radius_(radius),
  center_(center)
{
  if (radius_ < 0.0) 
  {
    throw std::invalid_argument("Error. Invalid radius of circle.");
  }
}

double Circle::getArea() const noexcept
{
  return (M_PI * radius_ * radius_);
}

rectangle_t Circle::getFrameRect() const noexcept
{
  return {2 * radius_, 2 * radius_, center_};
}

void Circle::move(const point_t & point) noexcept
{
  center_ = point;
}

void Circle::move(const double dx, const double dy) noexcept
{
  center_.x += dx;
  center_.y += dy;
}
