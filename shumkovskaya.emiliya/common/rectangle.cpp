#include "rectangle.hpp"
#include <stdexcept>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace shumkovskaya;

shumkovskaya::Rectangle::Rectangle(double w, double h, const shumkovskaya::point_t & p) :
    width_(w),
    height_(h),
    pos_(p),
    angle_(0.0)
{
    if (width_ <= 0)
    {
        throw std::invalid_argument("Invalid_rectangle_width");
    }
    if (height_ <= 0)
    {
        throw std::invalid_argument("Invalid_rectangle_heigth");
    }
}

double shumkovskaya::Rectangle::getArea() const
{
    return height_ * width_;
}

shumkovskaya::rectangle_t shumkovskaya::Rectangle::getFrameRect() const
{
  return {abs(width_ * cos((angle_*M_PI) / 180) + height_ * sin((angle_*M_PI) / 180)),
    abs(width_ * sin((angle_*M_PI) / 180) + height_ * cos((angle_*M_PI) / 180)), pos_ };

}

void shumkovskaya::Rectangle::move(const double dx, const double dy)
{
    pos_.x += dx;
    pos_.y += dy;
}

void shumkovskaya::Rectangle::move(const shumkovskaya::point_t & p)
{
    pos_ = p;
}

void shumkovskaya::Rectangle::scale(const double coefficient)
{
    if (coefficient < 0)
    {
      throw std::invalid_argument("Wrong coefficient");
    }
    width_ *= coefficient;
    height_ *= coefficient;
}

void shumkovskaya::Rectangle::rotate(const double angle) noexcept
{
    angle_ += angle;
    fmod(angle_, 360.0);
}
