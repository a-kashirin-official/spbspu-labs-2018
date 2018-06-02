#include "circle.hpp"

#include <math.h>
#include <stdexcept>

using namespace styagov;

styagov::Circle::Circle(const styagov::point_t & pos, const double radius):
  pos_(pos),
  radius_(radius),
  angle_(0.0)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Circle: Radius must be non-negative");
  }
}

double styagov::Circle::getRadius() const noexcept
{
  return radius_;
}

styagov::point_t styagov::Circle::getPos() const noexcept
{
  return pos_;
}

double styagov::Circle::getArea() const noexcept
{
  return M_PI * radius_ * radius_;
}

styagov::rectangle_t styagov::Circle::getFrameRect() const noexcept
{
  return { pos_, radius_ * 2, radius_ * 2 };
}

void styagov::Circle::move(const styagov::point_t &pos) noexcept
{
  pos_ = pos;
}

void styagov::Circle::move(const double dx, const double dy) noexcept
{
  pos_.x += dx;
  pos_.y += dy;
}

void styagov::Circle::scale(const double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("Circle: Ratio value must be non-negative");
  }

  radius_ *= ratio;
}

void styagov::Circle::rotate(const double alpha) noexcept
{
  angle_ += alpha;
  
  if (angle_ >= 360.0)
  {
    angle_ = fmod(angle_, 360.0);
  }
}
