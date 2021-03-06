#include "rectangle.hpp"
#include <iostream>
#include <stdexcept>

using namespace isaev;

Rectangle::Rectangle(const point_t &centre, double width, double height):
pos_(centre),
width_(width),
height_(height)
{
  if (width < 0.0 || height < 0.0)
  {
    throw std::invalid_argument("Sides of rectangle can't be negative");
  }//line and point are rectangles too
}
double Rectangle::getArea() const
{
  return (width_ * height_);
}
rectangle_t Rectangle::getFrameRect() const
{
  return {pos_, width_, height_};
}
void Rectangle::move(const point_t &point)
{
  pos_ = point;
}
void Rectangle::move(const double dx,const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}
void Rectangle::scale(const double ratio)
{
  if(ratio < 0.0)
  {
    throw std::invalid_argument("Ratio can't be negative");
  }
  width_ *= ratio;
  height_ *= ratio;
}
void Rectangle::printShapeInfo() const
{
  std::cout << "Rectangle info:\n";
  std::cout << "Centre: {" << pos_.x << "," << pos_.y << "}\n";
  std::cout << "Widht = " << width_ << "\n";
  std::cout << "Height = " << height_ << "\n";
}

