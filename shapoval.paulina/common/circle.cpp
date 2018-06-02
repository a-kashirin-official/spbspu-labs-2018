#include "circle.hpp"

#include <stdexcept>
#include <math.h>

shapoval::Circle::Circle(const shapoval::point_t & centre, const double radius) :
  centre_(centre),
  radius_(radius),
  angle_(0)
{
  if (radius < 0)
  {
    throw std::invalid_argument("Invalid circle!!");
  }
}

double shapoval::Circle::getArea() const noexcept
{
  return radius_ * radius_ * M_PI;
}

double shapoval::Circle::getAngle() const noexcept
{
  return angle_;
}

shapoval::rectangle_t shapoval::Circle::getFrameRect() const noexcept
{
  return {centre_, 2 * radius_, 2 * radius_};
}

void shapoval::Circle::scale(const double k)
{
  if (k < 0)
  {
    throw std::invalid_argument("Invalid k!!");
  }
  else
  {
  radius_ *= k;
  }
}

void shapoval::Circle::rotate(const double a) noexcept
{
  angle_ += a;
  if (angle_ >= 360)
  {
    angle_ = fmod(angle_, 360);
  }
}

void shapoval::Circle::move(const shapoval::point_t & new_centre) noexcept
{
  centre_ = new_centre;
}

void shapoval::Circle::move(const double dx, const double dy) noexcept
{
  centre_.x += dx;
  centre_.y += dy;
}
