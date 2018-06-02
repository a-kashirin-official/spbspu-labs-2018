#include "rectangle.hpp"
#include <stdexcept>
#include <math.h>

using namespace dumaev;

Rectangle::Rectangle(const point_t &point, const double width, const double height):
  pos_(point),
  width_(width),
  height_(height),
  angle_(0.0)
{
  if ((width_ < 0) || (height_ < 0))
  {
    throw std::invalid_argument("Width, height must be positive or zero");
  }
}

double Rectangle::getArea() const noexcept
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const noexcept
{
  const double sine = sin(angle_ * M_PI / 180);
  const double cose = cos(angle_ * M_PI / 180);
  const double width = height_ * abs(sine) + width_ * abs(cose);
  const double height = height_ * abs(cose) + width_ * abs(sine);
  return {pos_, width, height};
}

void Rectangle::move(const point_t &point) noexcept
{
  pos_ = point;
}

void Rectangle::move(const double dx, const double dy) noexcept
{
  pos_.x += dx;
  pos_.y += dy;
}

point_t Rectangle::getPos() const noexcept
{
  return pos_;
}

void Rectangle::scale(const double coefficient)
{
  if (coefficient < 0)
  {
    throw std::invalid_argument("Coefficient must be positive or zero");
  }
  width_ *= coefficient;
  height_ *= coefficient;
}

void Rectangle::rotate(const double angle) noexcept
{
  angle_ += angle;
  if (angle_ >= 360)
  {
    angle_ = fmod(angle_, 360.0);
  }
}
