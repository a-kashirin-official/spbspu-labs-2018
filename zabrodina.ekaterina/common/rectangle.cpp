#include "rectangle.hpp"

#include <iostream>


zabrodina::Rectangle::Rectangle(const point_t &position, const double w, const double h):
  pos_(position),
  width_(w),
  height_(h)
{
  if (width_<=0)
  {
    throw std::invalid_argument("Error: width<=0");
  }
  if (height_<=0)
  {
    throw std::invalid_argument("Error: height<=0");
  }
}

double zabrodina::Rectangle::getArea() const
{
  return width_ * height_;
}

zabrodina::rectangle_t zabrodina::Rectangle::getFrameRect() const
{
  return {height_,width_, {pos_.x,pos_.y}};
}

void zabrodina::Rectangle::move(const point_t &position)
{
 pos_ = position;
}

void zabrodina::Rectangle::move(const double ox, const double oy)
{
  pos_.x += ox;
  pos_.y += oy;
}

void zabrodina::Rectangle::printInf() const
{
  std::cout << "Area of a rectangle: " << zabrodina::Rectangle::getArea() << std::endl;
  std::cout<< "Height: " << height_ << " Width: " << width_ << std::endl;
  std::cout<< "Center: (" << pos_.x << "," << pos_.y << ")" <<std::endl;
  rectangle_t frame = getFrameRect();
  std::cout << "Frame Center ("<< frame.pos.x << "," << frame.pos.y << ")" << std::endl;
  std::cout << "Frame Width: " << frame.width << "   Frame Height: " << frame.height << std::endl;
}

void zabrodina::Rectangle::scale(const double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Error: coefficient <= 0");
  }
  else
  {
    height_ *= coefficient;
    width_  *= coefficient;
  }
}
