#include "rectangle.hpp"

#include <stdexcept>
#include <math.h>

shapoval::Rectangle::Rectangle(const shapoval::point_t & centre, const double width, const double height):
  centre_(centre),
  width_(width),
  height_(height),
  angle_(0)
{
  if ((width_ < 0) || (height_ < 0))
  {
    throw std::invalid_argument("Invalid rectangle!!");
  }
}

double shapoval::Rectangle::getArea() const noexcept
{
  return width_ * height_;
}

double shapoval::Rectangle::getAngle() const noexcept
{
  return angle_;
}

shapoval::rectangle_t shapoval::Rectangle::getFrameRect() const noexcept
{
  const double sine = sin(angle_ * M_PI / 180);
  const double cosine = cos(angle_ * M_PI / 180);
  const double width = fabs(width_ * cosine) + fabs(height_ * sine);
  const double height =  fabs(height_ * cosine) + fabs(width_ * sine);
  return {centre_, width, height};
}

void shapoval::Rectangle::scale(const double k)
{
  if (k < 0)
  {
    throw std::invalid_argument("Invalid k!!");
  }
  else
  {
    width_ *= k;
    height_ *= k;
  }
}

void shapoval::Rectangle::rotate(const double a) noexcept
{
  angle_ += a;
  if (fabs(angle_) >= 360)
  {
    angle_ = fmod(angle_, 360);
  }
}

void shapoval::Rectangle::move(const shapoval::point_t & new_centre) noexcept
{
  centre_ = new_centre;
}

void shapoval::Rectangle::move(const double dx, const double dy) noexcept
{
  centre_.x += dx;
  centre_.y += dy;
}
