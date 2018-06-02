#include "circle.hpp"

#include <stdexcept>
#include <math.h>

satyukov::Circle::Circle(const satyukov::point_t & center, const double radius):
  center_(center),
  radius_(radius),
  angle_(0.0)
{
  if (radius_ <= 0.0)
  {
    throw std::invalid_argument("Invalid radius");
  }
}

double satyukov::Circle::getArea() const noexcept
{
  return M_PI * radius_ * radius_;
}

double satyukov::Circle::getRadius() const noexcept
{
  return radius_;
}

double satyukov::Circle::getAngle() const noexcept
{
  return angle_;
}

satyukov::point_t satyukov::Circle::getCoordinates() const noexcept
{
  return { center_.x, center_.y };
}

satyukov::rectangle_t satyukov::Circle::getFrameRect() const noexcept
{
  return { center_, 2 * radius_, 2 * radius_ };
}

void satyukov::Circle::move(const satyukov::point_t & newCenter) noexcept
{
  center_ = newCenter;
}

void satyukov::Circle::move(const double dx, const double dy) noexcept
{
  center_.x += dx;
  center_.y += dy;
}

void satyukov::Circle::scale(const double coefficient)
{
  if (coefficient <= 0.0)
  {
    throw std::invalid_argument("Invalid coefficient");
  }
  radius_ *= coefficient;
}

void satyukov::Circle::rotate(const double angle) noexcept
{
  angle_ += angle;
  if (abs(angle_) >= 360.0)
  {
    angle_ = std::fmod(angle_, 360.0);
  }
}
