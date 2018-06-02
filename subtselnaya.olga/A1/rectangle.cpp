#include "rectangle.hpp"
#include <stdexcept>
#include <iostream>

Rectangle::Rectangle(const double width, const double height, const point_t & center):
  rect_({width, height, center})
{
  if (width < 0 || height < 0) {
    throw std::invalid_argument("Wrong parameters");
  }
}

double Rectangle::getArea() const
{
  return rect_.width * rect_.height;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rect_;
}

void Rectangle::move(const point_t & resPoint)
{
  rect_.pos = resPoint;
}

void Rectangle::move(const double dx, const double dy)
{
  rect_.pos.x += dx;
  rect_.pos.y += dy;
}

void Rectangle::printRect() const
{
  std::cout << "Rectangle has width - " << rect_.width << ", height - " << rect_.height << std::endl;
  std::cout << "  Center is in (" << rect_.pos.x << ", " << rect_.pos.y << ')' << std::endl;
}
