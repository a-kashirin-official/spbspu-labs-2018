#include "rectangle.hpp"
#include <iostream>
#include <cassert>


Rectangle::Rectangle(const point_t & center, const double width, const double height):
  center_(center),
  width_(width),
  heigth_(height)
{
  assert((width >= 0.0) && (height >= 0.0));
}

double Rectangle::getArea() const
{
  return width_*heigth_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_t{center_,width_,heigth_};
}

void Rectangle::move(const point_t & transferPoint)
{
  center_ = transferPoint;
}

void Rectangle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Rectangle::printCurrentInfo() const
{
  std::cout << "Rectangle center (x,y): " << center_.x << ", " << center_.y << std::endl;
  std::cout << "Rectangle width: " << width_ << std::endl;
  std::cout << "Rectangle height: " << heigth_ << std::endl;
}
