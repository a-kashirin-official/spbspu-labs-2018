#include "rectangle.hpp"
#include <stdexcept>
#include <math.h>

using namespace kashirin;

Rectangle::Rectangle(const double width,const double height, const point_t &pos):
  width_(width),
  height_(height),
  center_(pos),
  angle_(0)
{
  if (width <= 0 || height <= 0)
  {
    throw std::invalid_argument("Invalid argument");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  const double sine = sin(angle_ * M_PI / 180);
  const double cosine = cos(angle_ * M_PI / 180);
  const double width = fabs(height_ * sine) + fabs(width_ * cosine);
  const double height = fabs(height_ * cosine) + fabs(width_ * sine);
  return {width, height, center_};
}

point_t Rectangle::getCenter() const
{
  return center_;
}

void Rectangle::move(const point_t &newPoint)
{
  center_ = newPoint;
}

void Rectangle::move(const double dx,const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Rectangle::scale(const double coef)
{
  if (coef <= 0)
  {
    throw std::invalid_argument("Invalid coef");
  }
  width_ *= coef;
  height_ *= coef;
}

void Rectangle::rotate(const double angle)
{
  angle_ += angle;
  if (angle_ >= 360)
  {
    angle_ = fmod(angle_, 360);
  }
}
