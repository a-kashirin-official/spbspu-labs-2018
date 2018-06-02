#include <iostream>
#include "rectangle.hpp"

Rectangle::Rectangle(const point_t & rectCenter, const double w, const double h):
  centerRec_(rectCenter),
  width_(w),
  height_(h)
{
  if ((w < 0) || (h < 0))
  {
    std::cerr << "Invalid value." << std::endl;
  }
}

double Rectangle::getArea() const
{
  return width_*height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_t {width_, height_, centerRec_};
}

void Rectangle::move(double dx, double dy)
{
  centerRec_.x +=dx;
  centerRec_.y +=dy;
}

void Rectangle::move(const point_t &center)
{
 centerRec_ = center;
}

void Rectangle::printf()
{
  rectangle_t rect = getFrameRect();
  std::cout << "New coordinates of the center after moving to the point: " << centerRec_.x << "  " << centerRec_.y << std::endl;
  std::cout << "Width and height of the rectangle: " << rect.width << "  " << rect.height << std::endl;
  std::cout << "Area: " << Rectangle::getArea() << std::endl;
}

point_t Rectangle::getPos()
{
  return centerRec_;
}
