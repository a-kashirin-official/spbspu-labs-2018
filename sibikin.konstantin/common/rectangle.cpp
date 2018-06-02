#include "rectangle.hpp"
#include <stdexcept>
#include <cmath>

sibikin::Rectangle::Rectangle(const point_t & center, const double w, const double h):
  width_(w),
  height_(h),
  pos_(center),
  angle_(0)
{
  if ((h < 0.0) || (w < 0.0))
  {
    throw std::invalid_argument("height and width cannot be < 0");
  }
}

double sibikin::Rectangle::getArea() const
{
  return width_ * height_;
}

sibikin::rectangle_t sibikin::Rectangle::getFrameRect() const
{
  const double phi = angle_ * M_PI / 180;
  double width = height_ * fabs(sin(phi)) + width_ * fabs(cos(phi));
  double height = height_ * fabs(cos(phi)) + width_ * fabs(sin(phi));
  return {width, height, pos_};
}

sibikin::point_t sibikin::Rectangle::getPos() const
{
  return pos_;
}

void sibikin::Rectangle::move(const point_t & newCenter)
{
  pos_ = newCenter;
}

void sibikin::Rectangle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void sibikin::Rectangle::scale(const double coef)
{
  if (coef > 0.0)
  {
    width_ *= coef;
    height_ *= coef;
  }
  else
  {
    throw std::invalid_argument("coef must be > 0");
  }
}

void sibikin::Rectangle::rotate(const double phi)
{
  angle_ += phi;
}
