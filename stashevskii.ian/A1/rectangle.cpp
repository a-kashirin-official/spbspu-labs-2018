#include <iostream>
#include "rectangle.hpp"

Rectangle::Rectangle(const double width, const double height, const point_t& point):
  width_(width),
  height_(height),
  pos(point)
{
  if ((width < 0.0) || (height < 0.0))
  {
    std::cerr << "Height and Width must be > 0!" << std::endl;
  }

}

rectangle_t Rectangle::getFrameRect() const
{
  return{ width_, height_, pos};
}

double Rectangle::getArea() const
{
  return(width_ * height_);
}

void Rectangle::move(const double dx, const double dy)
{
  pos.x += dx;
  pos.y += dy;
}

void Rectangle::move(const point_t &point)
{
  pos.x = point.x;
  pos.y = point.y;
}

void Rectangle::printf() const
{
  std::cout << "Rectangle:" << std::endl;
  std::cout << "  Width: " << width_ << "  Position:";
  std::cout << "    x: " << pos.x << "   y: " << pos.y << std::endl;
  std::cout << "  Area: " << Rectangle::getArea() << std::endl;

}
