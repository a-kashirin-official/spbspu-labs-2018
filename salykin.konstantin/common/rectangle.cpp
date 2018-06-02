#include <iostream>

#include "rectangle.hpp"

salykin::Rectangle::Rectangle(const double width, const double height, const salykin::point_t & center):
  center_(center),
  width_(width),
  height_(height)
{
  if ((width_ < 0.0) || (height_ < 0.0)) {
    throw std::invalid_argument("Invalid width or/and height");
  }
}

double salykin::Rectangle::getArea() const
{
  return (width_ * height_);
}

salykin::rectangle_t salykin::Rectangle::getFrameRect() const
{
  return {width_, height_, center_};
}

void salykin::Rectangle::move(const salykin::point_t & newPos)
{
  center_ = newPos;
}

void salykin::Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

salykin::point_t salykin::Rectangle::getPos() const
{
  return center_;
}

void salykin::Rectangle::scale(const double multiplier)
{
  if (multiplier < 0.0)
  {
    throw std::invalid_argument("Invalid multiplier");
  }
  width_ *= multiplier;
  height_ *= multiplier;
}

double salykin::Rectangle::getHeight() const
{
  return height_;
}

double salykin::Rectangle::getWidth() const
{
  return width_;
}
