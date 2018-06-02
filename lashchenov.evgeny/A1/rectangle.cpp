#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(double width, double height, point_t center) :
  width_(width),
  height_(height),
  center_(center)
{
  if (width_ < 0) {
    std::cerr << "Invalid rectangle width" << std::endl;
  }
  if (height_ < 0) {
    std::cerr << "Invalid rectangle height" << std::endl;
  }
}

Rectangle::Rectangle(double width, double height, double x, double y) :
  width_(width),
  height_(height)
{
  center_.x = x;
  center_.y = y;
  if (width_ < 0) {
    std::cerr << "Invalid rectangle width" << std::endl;
  }
  if (height_ < 0) {
    std::cerr << "Invalid rectangle height" << std::endl;
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {width_, height_, {center_.x, center_.y}};
}

void Rectangle::move(const point_t & center)
{
  center_ = center;
}

void Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Rectangle::printInfo() const
{
  std::cout << "It is rectangle" << '\n';
  std::cout << "Width: " << width_ << '\n';
  std::cout << "Height: " << height_ << '\n';
  std::cout << "Center: ";
  std::cout << "x = " << center_.x << ", y = " << center_.y << '\n' << std::endl;
}
