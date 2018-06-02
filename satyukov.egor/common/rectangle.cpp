#include "rectangle.hpp"

#include <stdexcept>
#include <math.h>

satyukov::Rectangle::Rectangle(const satyukov::point_t & center, const double width, const double height):
  center_(center),
  width_(width),
  height_(height),
  angle_(0.0)
{
  if (width_ <= 0.0)
  {
    throw std::invalid_argument("Invalid width");
  }
  if (height_ <= 0.0)
  {
    throw std::invalid_argument("Invalid height");
  }
}

double satyukov::Rectangle::getArea() const noexcept
{
  return width_ * height_;
}

double satyukov::Rectangle::getWidth() const noexcept
{
  return width_;
}

double satyukov::Rectangle::getHeight() const noexcept
{
  return height_;
}

double satyukov::Rectangle::getAngle() const noexcept
{
  return angle_;
}

satyukov::point_t satyukov::Rectangle::getCoordinates() const noexcept
{
  return { center_.x, center_.y };
}

satyukov::rectangle_t satyukov::Rectangle::getFrameRect() const noexcept
{
  const double sine = sin(angle_ * M_PI / 180.0);
  const double cosine = cos(angle_ * M_PI / 180.0);
  return { center_, width_ * abs(cosine) + height_ * abs(sine), height_ * abs(cosine) + width_ * abs(sine) };
}

void satyukov::Rectangle::move(const satyukov::point_t & newCenter) noexcept
{
  center_ = newCenter;
}

void satyukov::Rectangle::move(const double dx, const double dy) noexcept
{
  center_.x += dx;
  center_.y += dy;
}

void satyukov::Rectangle::scale(const double coefficient)
{
  if (coefficient <= 0.0)
  {
    throw std::invalid_argument("Invalid coefficient");
  }
  width_ *= coefficient;
  height_ *= coefficient;
}

void satyukov::Rectangle::rotate(const double angle) noexcept
{
  angle_ += angle;
  if (abs(angle_) >= 360.0)
  {
    angle_ = std::fmod(angle_, 360.0);
  }
}
