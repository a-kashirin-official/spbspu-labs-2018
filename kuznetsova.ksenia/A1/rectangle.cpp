#include "rectangle.hpp"
#include <iostream>


Rectangle::Rectangle(point_t &centre, double width, double height) :
centre_(centre)
{
  if (width < 0) {
    width_ = 0;
    std::cout << "Width cannot be negative" << std::endl;
  }
  else{
    width_ = width;
  }
  if (height < 0) {
    height_ = 0;
    std::cout << "Height cannot be negative" << std::endl;
  }
  else{
    height_ = height;
  }
}
double Rectangle::getArea() const
{
  return width_ * height_;
}
rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_t{ centre_, width_, height_ };
}
void Rectangle::move(point_t &newcentre)
{
  centre_ = newcentre;
}
void Rectangle::move(double dx, double dy)
{
  centre_.x += dx;
  centre_.y += dy;
}
