#include "circle.hpp"
#include <cmath>
#include <cassert>
#include <stdexcept>

shapovalova::Circle::Circle(const point_t & pos, const double radius) :
  position_(pos),
  radius_(radius),
  angle_(0.0)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Invalid radius");
  }
}

double shapovalova::Circle::getArea() const noexcept
{
  return M_PI * radius_ * radius_;
}

shapovalova::rectangle_t shapovalova::Circle::getFrameRect() const noexcept
{
  return {position_, radius_ * 2, radius_ * 2};
}

void shapovalova::Circle::move(const point_t & posTo) noexcept
{
  position_ = posTo;
}

void shapovalova::Circle::move(const double dx, const double dy) noexcept
{
  position_.x += dx;
  position_.y += dy;
}

void shapovalova::Circle::scale(const double coefficient)
{
  if (coefficient <= 0.0)
  {
    throw std::invalid_argument ("Invalid parameter of scaling");
  }
  radius_ *= coefficient;
}

void shapovalova::Circle::rotate(const double degrees) noexcept
{
  angle_ += degrees;
  if (angle_ >= 360.0)
  {
    angle_ = fmod(angle_, 360);
  }
}
