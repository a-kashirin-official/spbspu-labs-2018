#include "rectangle.hpp"

#include <math.h>
#include <stdexcept>

using namespace styagov;

styagov::Rectangle::Rectangle(const styagov::point_t & pos, const double width, const double height):
  pos_(pos),
  width_(width),
  height_(height),
  angle_(0.0)
{
  if (width < 0.0)
  {
    throw std::invalid_argument("Rectangle: Width value must be non-negative");
  }
  if (height < 0.0)
  {
    throw std::invalid_argument("Rectangle: Height value must be non-negative");
  }
}

void styagov::Rectangle::setWidth(const double width)
{
  if (width < 0.0)
  {
    throw std::invalid_argument("Rectangle: Width value must be non-negative");
  }

  width_ = width;
}

double styagov::Rectangle::getWidth() const noexcept
{
  return width_;
}

void styagov::Rectangle::setHeight(const double height)
{
  if (height < 0.0)
  {
    throw std::invalid_argument("Rectangle: Height value must be non-negative");
  }

  height_ = height;
}

double styagov::Rectangle::getHeight() const noexcept
{
  return height_;
}

styagov::point_t styagov::Rectangle::getPos() const noexcept
{
  return pos_;
}

double styagov::Rectangle::getArea() const noexcept
{
  return width_ * height_;
}

styagov::rectangle_t styagov::Rectangle::getFrameRect() const noexcept
{
  // translating degrees into radians
  const double sinAlpha = sin(angle_ * M_PI / 180.0);
  const double cosAlpha = cos(angle_ * M_PI / 180.0);

  const double width = height_ * fabs(sinAlpha) + width_ * fabs(cosAlpha);
  const double height = height_ * fabs(cosAlpha) + width_ * fabs(sinAlpha);

  return { pos_, width, height };
}

void styagov::Rectangle::move(const styagov::point_t &pos) noexcept
{
  pos_ = pos;
}

void styagov::Rectangle::move(const double dx, const double dy) noexcept
{
  pos_.x += dx;
  pos_.y += dy;
}

void styagov::Rectangle::scale(const double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("Rectangle: Ratio value must be non-negative");
  }

  width_  *= ratio;
  height_ *= ratio;
}

void styagov::Rectangle::rotate(const double alpha) noexcept
{
  angle_ += alpha;

  if (angle_ >= 360.0)
  {
    angle_ = fmod(angle_, 360.0);
  }
}
