#include <iostream>
#include <stdexcept>
#include "rectangle.hpp"

Rectangle::Rectangle(const point_t & center, const double & height, const double & width) :
  cntr_(center),
  height_(height),
  width_(width)
{
  if ((width_ < 0.0) || (height_ < 0.0))
  {
    throw std::invalid_argument("Invalid Parameters!");
  }
}

void Rectangle::move(const point_t & Center)
{
  cntr_ = Center;
}

void Rectangle::move(const double add_x, const double add_y)
{
  cntr_.x += add_x;
  cntr_.y += add_y;
}

double Rectangle::getArea() const
{
  return width_*height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {cntr_, height_, width_};
}

void Rectangle::print() const
{
  std::cout << "Rectangle center:" << cntr_.x << "; " << cntr_.y << std::endl;
  std::cout << "Rectangle height:" << height_ << std::endl;
  std::cout << "Rectangle width:" << width_ << std::endl;
  std::cout << "Rectangle area:" << getArea() << std::endl;
}        
