#include <iostream>
#include "rectangle.hpp"


Rectangle::Rectangle(const double width, const double height, const point_t &poss) :
  center_(poss)
{
  if (width < 0 || height < 0) {
    std::cerr << "Width and height of the rectangle must be > 0!" << std::endl;
  }
  width_ = width;
  height_ = height;
  center_ = poss;
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {height_, width_, {center_.x, center_.y}};
}

void Rectangle::move(const point_t &poss)
{
  center_ = poss;
}

void Rectangle::move(double Ox, double Oy)
{
  center_.x += Ox;
  center_.y += Oy;
}

void Rectangle::OutInf() const
{
  std::cout << "Center( " << center_.x << " ; " << center_.y << " )" << std::endl;
  std::cout << "Width:  " << getFrameRect().width << std::endl;
  std::cout << "Height: " << getFrameRect().height << std::endl;
  std::cout << "Area:   " << getArea() << std::endl;
  std::cout << "_____________________ " << std::endl;
}
