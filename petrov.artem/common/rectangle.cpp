#include "rectangle.hpp"

#include <stdexcept>
#include <math.h>

petrov::Rectangle::Rectangle(const petrov::point_t & middle, const double width, const double height):
  middle_(middle),
  width_(width),
  height_(height),
  angle_(0.0)
{
  if ((width < 0.0) || (height < 0.0))
  {
    throw std::invalid_argument("Invalid rectangle");
  }
}

double petrov::Rectangle::getArea() const noexcept
{
  return width_ * height_;
}

petrov::rectangle_t petrov::Rectangle::getFrameRect() const noexcept
{
  const double sine = sin(angle_ * M_PI / 180);
  const double cosine = cos(angle_ * M_PI / 180);
  const double width = height_ * abs(sine) + width_ * abs(cosine);
  const double height = height_ * abs(cosine) + width_ * abs(sine);
  return {middle_, width, height};
}

void petrov::Rectangle::move(const petrov::point_t & pos) noexcept
{
  middle_ = pos;
}

void petrov::Rectangle::move(const double dx, const double dy) noexcept
{
  middle_.x += dx;
  middle_.y += dy;
}

void petrov::Rectangle::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Invalid factor");
  }
  width_ *= factor;
  height_ *= factor;
}

void petrov::Rectangle::rotate(const double angle) noexcept
{
  angle_ += angle;
  if (angle_ >= 360)
  {
    angle_ = fmod(angle_, 360.0);
  }
}
