#include "rectangle.hpp"

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdexcept>

using namespace semakina;

Rectangle::Rectangle(const point_t & center, const double w, const double h):
  pos_(center),
  width_(w),
  height_(h),
  degree_(0)
{
  if (width_ <= 0)
  {
    throw std::invalid_argument("Invalid rectangle's width");
  }
  if (height_ <= 0)
  {
    throw std::invalid_argument("Invalid rectangle's height");
  }
}

void Rectangle::move(const point_t & pos) noexcept
{
  pos_ = pos;
}

void Rectangle::move(const double dx, const double dy) noexcept
{
  pos_.x += dx;
  pos_.y += dy;
}

double Rectangle::getArea() const noexcept
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const noexcept
{
  return {height_ * sin(degree_ * M_PI / 180) + width_ * cos(degree_ * M_PI / 180),
           height_ * cos(degree_ * M_PI / 180) + width_ * sin(degree_ * M_PI / 180), {pos_.x, pos_.y}};
}

void Rectangle::scale(const double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Invalid coefficient");
  }
  width_ *= coefficient;
  height_ *= coefficient;
}

void Rectangle::rotate(const double degree) noexcept
{
  degree_ += degree;
}
