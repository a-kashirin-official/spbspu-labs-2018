#include "rectangle.hpp"
#include <iostream>

mironenkov::Rectangle::Rectangle(const point_t & pos, const double width, const double height):
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

double mironenkov::Rectangle::getArea() const
{
  return width_ * height_;
};

mironenkov::rectangle_t mironenkov::Rectangle::getFrameRect() const
{
  return rectangle_t{width_, height_, pos_};
};

void mironenkov::Rectangle::move(const double dx, const double dy)
{
    pos_.x += dx;
    pos_.y += dy;
};

void mironenkov::Rectangle::move(const point_t & pos)
{
  pos_ = pos;
};

void mironenkov::Rectangle::scale(const double coeff)
{
  if (coeff <= 0.0)
  {
    throw std::invalid_argument("Scale coeff is invalid!");
  }
  width_ *= coeff;
  height_ *= coeff;
};
