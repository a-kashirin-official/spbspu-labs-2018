#include "circle.hpp"

#include <iostream>
#include <math.h>

using namespace afanasiev;

afanasiev::Circle::Circle(const point_t & center, const double radius):
  center_(center),
  radius_(radius),
  angle_(0.0)
{
  if (radius_ < 0.0)
  {
    throw std::invalid_argument("Radius must be > 0.0");
  }
}

double afanasiev::Circle::getArea() const noexcept
{
  return M_PI * radius_ * radius_;
}

rectangle_t afanasiev::Circle::getFrameRect() const noexcept
{
  return { 2 * radius_, 2 * radius_, center_ };
}

void afanasiev::Circle::move(const point_t & newPos) noexcept
{
  center_ = newPos;
}

void afanasiev::Circle::move(const double dx, const double dy) noexcept
{
  center_.x += dx;
  center_.y += dy;
}

point_t afanasiev::Circle::getPos() const noexcept
{
  return center_;
}

double afanasiev::Circle::getRadius() const noexcept
{
  return radius_;
}

void afanasiev::Circle::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Invalid factor");
  }
  radius_ *= factor;
}

void afanasiev::Circle::rotate(const double angle) noexcept
{
  angle_ += angle;
  if (angle_ >= 360)
  {
    angle_ = fmod(angle_, 360.0);
  }
}

