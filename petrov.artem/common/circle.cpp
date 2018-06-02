#include "circle.hpp"

#include <stdexcept>
#include <math.h>

petrov::Circle::Circle(const petrov::point_t & centre, const double radius):
  centre_(centre),
  radius_(radius),
  angle_(0.0)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Invalid circle");
  }
}

double petrov::Circle::getArea() const noexcept
{
  return M_PI * radius_ * radius_;
}

petrov::rectangle_t petrov::Circle::getFrameRect() const noexcept
{
  return {centre_, 2 * radius_, 2 * radius_};
}

void petrov::Circle::move(const petrov::point_t & pos) noexcept
{
  centre_ = pos;
}

void petrov::Circle::move(const double dx, const double dy) noexcept
{
  centre_.x += dx;
  centre_.y += dy;
}

void petrov::Circle::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Invalid factor");
  }
  radius_ *= factor;
}

void petrov::Circle::rotate(const double angle) noexcept
{
  angle_ += angle;
  if (angle_ >= 360)
  {
    angle_ = fmod(angle_, 360.0);
  }
}
