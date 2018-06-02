#include "rectangle.hpp"
#include <iostream>

khmyrov::Rectangle::Rectangle(const point_t & pos, const double width, const double height):
  Shape(pos)
{
  if (width < 0.0)
  {
    throw std::invalid_argument("Width is invalid!");
  }
  else if (height < 0.0)
  {
    throw std::invalid_argument("Height is invalid!");
  }
  width_ = width;
  height_ = height;
};

double khmyrov::Rectangle::getArea() const
{
  return width_ * height_;
};

khmyrov::rectangle_t khmyrov::Rectangle::getFrameRect() const
{
  return rectangle_t{width_, height_, pos_};
};

void khmyrov::Rectangle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
};

void khmyrov::Rectangle::move(const point_t & pos)
{
  pos_ = pos;
};

void khmyrov::Rectangle::scale(const double coeff)
{
  if (coeff <= 0.0)
  {
    throw std::invalid_argument("Scale coeff is invalid!");
  }
  width_ *= coeff;
  height_ *= coeff;
};

