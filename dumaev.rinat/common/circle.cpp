#include "circle.hpp"
#include <stdexcept>
#include <math.h>

using namespace dumaev;

Circle::Circle(const point_t &point, const double radius):
  pos_(point),
  radius_(radius),
  angle_(0.0)
{
  if (radius < 0)
  {
    throw std::invalid_argument("Radius must be positive or zero");
  }
}

double Circle::getArea() const noexcept
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const noexcept
{
  rectangle_t rectangle = {pos_, radius_ * 2, radius_ * 2};
  return rectangle;
}

void Circle::move(const point_t &point) noexcept
{
  pos_ = point;
}

void Circle::move(const double dx, const double dy) noexcept
{
  pos_.x += dx;
  pos_.y += dy;
}

point_t Circle::getPos() const noexcept
{
  return pos_;
}

void Circle::scale(const double coefficient)
{
  if (coefficient < 0)
  {
    throw std::invalid_argument("Coefficient must be positive or zero");
  }
  radius_ *= coefficient;
}

void Circle::rotate(const double angle) noexcept
{
  angle_ += angle;
  if (angle_ >= 360)
  {
    angle_ = fmod(angle_,360.0);
  }
}
