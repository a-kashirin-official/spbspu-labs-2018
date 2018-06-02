#include "rectangle.hpp"

#include <iostream>
#include <math.h>

using namespace afanasiev;

afanasiev::Rectangle::Rectangle(const double width, const double height, const point_t & mid):
  mid_(mid),
  width_(width),
  height_(height),
  angle_(0.0)
{
  if (width_ < 0.0)
  {
    throw std::invalid_argument("Width must be > 0.0");
  }
  if (height_ < 0.0)
  {
    throw std::invalid_argument("Height must be > 0.0");
  }
}

double afanasiev::Rectangle::getArea() const noexcept
{
  return height_ * width_;
}

rectangle_t afanasiev::Rectangle::getFrameRect() const noexcept
{

  const double sine = sin(angle_ * M_PI / 180);
  const double cosine = cos(angle_ * M_PI / 180);
  const double width = height_ * abs(sine) + width_ * abs(cosine);
  const double height = height_ * abs(cosine) + width_ * abs(sine);
  return {width, height, mid_};

}

void afanasiev::Rectangle::move(const point_t & newPos) noexcept
{
  mid_ = newPos;
}

void afanasiev::Rectangle::move(const double dx, const double dy) noexcept
{
  mid_.x += dx;
  mid_.y += dy;
}

point_t afanasiev::Rectangle::getPos() const noexcept
{
 return mid_;
}

double afanasiev::Rectangle::getHeight() const noexcept
{
 return height_;
}

double afanasiev::Rectangle::getWidth() const noexcept
{
  return width_;
}

void afanasiev::Rectangle::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Invalid factor");
  }
  width_ *= factor;
  height_ *= factor;
}

void afanasiev::Rectangle::rotate(const double angle) noexcept
{
  angle_ += angle;
  if (angle_ >= 360)
  {
    angle_ = fmod(angle_, 360.0);
  }
}


