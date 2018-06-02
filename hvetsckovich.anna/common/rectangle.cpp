#include "rectangle.hpp"

#include <math.h>
#include <stdexcept>

using namespace hvetsckovich;

hvetsckovich::Rectangle::Rectangle(const point_t & pos, const double width, const double height):
  pos_(pos),
  width_(width),
  height_(height),
  angle_(0.0)
{
  if (width < 0.0)
  {
    throw std::invalid_argument("Width must be > 0");
  }
  if (height < 0.0)
  {
    throw std::invalid_argument("Height must be > 0");
  }
}

point_t hvetsckovich::Rectangle::getPos() const
{
  return pos_;
}

double hvetsckovich::Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t hvetsckovich::Rectangle::getFrameRect() const
{
  const double sina = sin(angle_ * M_PI / 180.0); // degrees -> radians
  const double cosa = cos(angle_ * M_PI / 180.0);
  const double width = height_ * abs(sina) + width_ * abs(cosa);
  const double height = height_ * abs(cosa) + width_ * abs(sina);
  return { pos_, width, height };
}

void hvetsckovich::Rectangle::move(const point_t & pos)
{
  pos_ = pos;
}

void hvetsckovich::Rectangle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void hvetsckovich::Rectangle::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Scale factor must be > 0");
  }

  width_  *= factor;
  height_ *= factor;
}

void hvetsckovich::Rectangle::rotate(const double degrees)
{
  angle_ += degrees;

  if (angle_ >= 360.0)
  {
    angle_ = fmod(angle_, 360.0);
  }
}
