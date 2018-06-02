#include <iostream>
#include "rectangle.hpp"


Rectangle::Rectangle(const double width, const double height, const point_t &pos) :
  center_(pos)
{
  if (width <= 0 || height <= 0) {
    std::cerr << "Width and height of the rectangle must be > 0!";
  }
  width_ = width;
  height_ = height;
}

Rectangle::Rectangle(double x, double y, double width, double height) :
  width_(width),
  height_(height),
  center_({x, y})
{
  if (width <= 0 || height <= 0) {
    std::cerr << "Width and height of the rectangle must be > 0!";
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

void Rectangle::move(double Ox, double Oy)
{
  center_.x += Ox;
  center_.y += Oy;
}

void Rectangle::printInfo()
{
  std::cout << "RECTANGLE:" << std::endl;
}

