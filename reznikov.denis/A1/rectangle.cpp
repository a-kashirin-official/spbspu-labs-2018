#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(double width, double height, const point_t &center) :
  width_(width),
  height_(height),
  center_(center)
{
  if ((width < 0.0) || (height < 0.0))
  {
    std::cerr << "Height and Width must be > 0!" << std::endl;
  }

}

rectangle_t Rectangle::getFrameRect() const
{
  return{ width_, height_, center_ };
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

void Rectangle::move(const point_t &point)
{
  center_ = point;
}

void Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Rectangle::inf() const
{
  std::cout << "Rectangle:" << "  Width: " << width_ << "  Height: " << height_ << std::endl;
  std::cout << "  Position:" << "    x: " << center_.x << "    y: " << center_.y << std::endl;
  std::cout << "  Area: " << this->getArea() << std::endl;
}
