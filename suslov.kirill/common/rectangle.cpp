#include "rectangle.hpp"

#include <stdexcept>
#include <math.h>

suslov::Rectangle::Rectangle(const suslov::point_t & center, const double width, const double height):
  center_(center),
  width_(width),
  height_(height),
  angle_(0.0)

{
  if (width < 0.0)
  {
    throw std::invalid_argument("Invalid rectangle width");
  }
  if (height < 0.0)
  {
    throw std::invalid_argument("Invalid rectangle height");
  }
}

suslov::rectangle_t suslov::Rectangle::getFrameRect() const noexcept
{
  const double frameWidth = width_ * abs(cos(angle_ * M_PI / 180.0)) + height_ * abs(sin(angle_ * M_PI / 180.0));
  const double frameHeight = width_ * abs(sin(angle_ * M_PI / 180.0)) + height_ * abs(cos(angle_ * M_PI / 180.0));
  return { center_, frameWidth, frameHeight };
}

double suslov::Rectangle::getArea() const noexcept
{
  return width_ * height_;
}

double suslov::Rectangle::getAngle() const noexcept
{
  return angle_;
}

void suslov::Rectangle::move(const double dx, const double dy) noexcept
{
  center_.x += dx;
  center_.y += dy;
}

void suslov::Rectangle::move(const suslov::point_t & newPoint) noexcept
{
  center_ = newPoint;
}

void suslov::Rectangle::scale(const double coef)
{
  if (coef < 0.0)
  {
    throw std::invalid_argument("Invalid coefficient");
  }
  else 
  {
    width_ *= coef;
    height_ *= coef;
  }
}

void suslov::Rectangle::rotate(const double angle) noexcept
{
  angle_ += angle;
}
