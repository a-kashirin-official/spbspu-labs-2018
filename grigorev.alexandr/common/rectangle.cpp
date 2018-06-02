#include "rectangle.hpp"
#include <iostream>
#include <math.h>

grigorev::Rectangle::Rectangle(const grigorev::point_t & center,const double width,const double height):
  center_(center),
  width_(width),
  height_(height),
  angle_(0.0)
{
  if (width < 0.0 || height < 0.0)
  {
    throw std::invalid_argument("Error: Invalid width or heigth");
  }
}

double grigorev::Rectangle::getArea() const
{
  return width_ * height_;
}

grigorev::rectangle_t grigorev::Rectangle::getFrameRect() const
{
  const double sine = sin(angle_ * M_PI / 180);
  const double cosine = cos(angle_ * M_PI / 180);
  return {center_, height_ * abs(sine) + width_ * abs(cosine), height_ * abs(cosine) + width_ * abs(sine)};
}

void grigorev::Rectangle::move(const grigorev::point_t & newCenter)
{
  center_ = newCenter;
}

void grigorev::Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void grigorev::Rectangle::scale(const double coef)
{
  if (coef < 0.0)
  {
    throw std::invalid_argument("Error: Invalid scale coef");
  }
  width_ *= coef;
  height_ *= coef;
}

void grigorev::Rectangle::rotate(const double angle)
{
  angle_ += angle;
  if (abs(angle_) >= 360.0)
  {
    angle_ = std::fmod(angle_, 360.0);
  }
}

