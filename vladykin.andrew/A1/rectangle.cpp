#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(const point_t &pos, const double width, const double height) :
  pos_(pos),
  width_(width),
  height_(height)
{
  if ((width_ <= 0.0) || (height_ <= 0.0))
  {
    std::cerr << "Wrong size of the rectangle." << std::endl;
  }
}

double Rectangle::getArea() const
{
  return (width_ * height_);
}

rectangle_t Rectangle::getFrameRect() const
{
  return { width_,height_,{pos_.x, pos_.y} };
}

void Rectangle::showSize() const
{
  std::cout << "The size of the rectangle: ";
  std::cout << "Width = " << width_ << " Height = " << height_ << std::endl;
}

void Rectangle::showPos() const
{
  std::cout << "Coordinates of the center of the rectangle: ";
  std::cout << "X = " << pos_.x << " Y = " << pos_.y << std::endl;
}

void Rectangle::move(const point_t &pos)
{
  pos_ = pos;
}

void Rectangle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}
