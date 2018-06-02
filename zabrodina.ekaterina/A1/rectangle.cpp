#include "rectangle.hpp"

#include <iostream>

Rectangle::Rectangle(const point_t &position, const double w, const double h):
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

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {height_,width_, {pos_.x,pos_.y}};
}

void Rectangle::move(const point_t &position)
{
  pos_ = position;
}

void Rectangle::move(const double ox, const double oy)
{
  pos_.x += ox;
  pos_.y += oy;
}

void Rectangle::printInf()
{
  std::cout << "Area of a rectangle: " << Rectangle::getArea() << std::endl;
  std::cout << "Height: " << height_ << " Width: " << width_ << std::endl;
  std::cout << "Center: (" << pos_.x << "," << pos_.y << ")" << std::endl;
  rectangle_t frame = getFrameRect();
  std::cout << "Frame Center (" << frame.pos.x << "," << frame.pos.y << ")" << std::endl;
  std::cout << "Frame Width: " << frame.width << "   Frame Height: " << frame.height << std::endl;
}
