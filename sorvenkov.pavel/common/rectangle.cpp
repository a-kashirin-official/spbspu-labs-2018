#include <iostream>

#include "rectangle.hpp"

using namespace sorvenkov;

Rectangle::Rectangle(const double width, const double height, const point_t& pos) :
  width_(width),
  height_(height),
  center_(pos)
{
  if (width < 0.0 || height < 0.0) 
  {
    throw std::invalid_argument("Width and height of the rectangle must be greater than zero");
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

void Rectangle::move(const point_t& pos)
{
  center_ = pos;
}

void Rectangle::move(double Ox, double Oy)
{
  center_.x += Ox;
  center_.y += Oy;
}
void Rectangle::scale(double ratio)
{
  if (ratio < 0) 
  {
    throw std::invalid_argument("Scale ratio must be greater than zero");
  }
  width_ *= ratio;
  height_ *= ratio;
}
