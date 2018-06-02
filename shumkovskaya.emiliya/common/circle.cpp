#include "circle.hpp"
#include <stdexcept>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace shumkovskaya;

shumkovskaya::Circle::Circle(const double r, const point_t & p) :
  radius_(r),
  pos_(p),
  angle_(0)
{
  if (radius_ < 0)
  {
    throw std::invalid_argument("Invalid_circle_radius");
  }
}

double shumkovskaya::Circle::getArea() const
{
  return  M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return { 2 * radius_, 2 * radius_, pos_ };
}

void shumkovskaya::Circle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void shumkovskaya::Circle::move(const point_t & p)
{
  pos_ = p;
}

void Circle::scale(const double coefficient)
{
  if (coefficient < 0)
  {
    throw std::invalid_argument("Wrong coefficient");
  }
  radius_ *= coefficient;
}

void shumkovskaya::Circle::rotate(const double angle) noexcept
{
  angle_ += angle;
  fmod(angle_, 360.0);
}
