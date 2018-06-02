#include "circle.hpp"
#include <stdexcept>
#include <cmath>

spodeneyko::Circle::Circle(const double radius, const point_t & center):
  radius_(radius),
  center_(center)
{
  if (radius_ < 0.0) 
  {
    throw std::invalid_argument("Error. Invalid radius of circle.");
  }
}

double spodeneyko::Circle::getArea() const noexcept
{
  return (M_PI * radius_ * radius_);
}

spodeneyko::rectangle_t spodeneyko::Circle::getFrameRect() const noexcept
{
  return {2 * radius_, 2 * radius_, center_};
}

std::string spodeneyko::Circle::getName() const noexcept
{
  return "Circle";
}

void spodeneyko::Circle::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Error. Invalid parameter of scaling.");
  }
  radius_ *= factor;
}

void spodeneyko::Circle::move(const point_t & point) noexcept
{
  center_ = point;
}

void spodeneyko::Circle::move(const double dx, const double dy) noexcept
{
  center_.x += dx;
  center_.y += dy;
}

void spodeneyko::Circle::rotate(const double /*angle*/) noexcept
{
}
