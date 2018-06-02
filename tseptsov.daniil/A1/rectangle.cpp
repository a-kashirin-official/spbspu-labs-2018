#include <iostream>
#include "rectangle.hpp"

Rectangle::Rectangle(const double width, const double height, const point_t &pos) :
  width_(width),
  height_(height),
  center_(pos)
{
  if (width < 0.0 || height < 0.0) {
    std::cerr << "Width and height of the rectangle must be > 0" << std::endl;
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {height_, width_, {center_.x, center_.y}};
}

void Rectangle::move(const point_t &pos)
{
  center_ = pos;
}

void Rectangle::move(const double Ox, const double Oy)
{
  center_.x += Ox;
  center_.y += Oy;
}

void Rectangle::OutData() const
{
  std::cout << "Width: " << width_ << std::endl;
  std::cout << "Height: " << height_ << std::endl;
  std::cout << "Spot of middle on Ox = " << center_.x << std::endl;
  std::cout << "Spot of middle on Oy = " << center_.y << std::endl;
}


