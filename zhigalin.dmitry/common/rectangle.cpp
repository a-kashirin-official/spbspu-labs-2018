#include "rectangle.hpp"
#include <iostream>

zhigalin::Rectangle::Rectangle(const point_t & pos, const double width, const double height):
  Shape(pos)
{
  if (width < 0.0)
  {
    throw std::invalid_argument("Width must be positive!");
  }
  else if (height < 0.0)
  {
    throw std::invalid_argument("Height must be positive!");
  }
  width_ = width;
  height_ = height;
};

double zhigalin::Rectangle::getArea() const
{
  return width_ * height_;
};

zhigalin::rectangle_t zhigalin::Rectangle::getFrameRect() const
{
  return rectangle_t{width_, height_, pos_};
};

void zhigalin::Rectangle::move(const point_t & pos)
{
  pos_ = pos;
};

void zhigalin::Rectangle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
};

void zhigalin::Rectangle::scale(const double coeff)
{
  if (coeff <= 0.0) 
  {
    throw std::invalid_argument("Scale coefficient must be positive!");
  }
  width_ *= coeff;
  height_ *= coeff;
};
