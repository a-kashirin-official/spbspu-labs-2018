#include <iostream>
#include "rectangle.hpp"

using std::cout;
using std::endl;

Rectangle::Rectangle(double h, double w, double x, double y) :
  center_({x, y}),
  height_(h),
  width_(w)
{
  if (h < 0.0 || w < 0.0)
  {
    throw std::invalid_argument("Width and height of the rectangle must be > 0, or = 0 for degenerate figure");
  }
}

void Rectangle::printInfo() const
{
  cout << ">>>RECTANGLE"<< endl;
  cout << "Area of rectangle: " << getArea() << endl;
  cout << "Cords of center of rectangle: " << center_.x << " " << center_.y << endl;
  rectangle_t frec;
  frec = getFrameRect();
  cout << "FRAME RECTANGLE" << endl << "Height: " << frec.height << endl;
  cout << "Width: " << frec.width << endl << "x, y cords: " << frec.pos.x << " " << frec.pos.y << endl << endl;
}

void Rectangle::move(point_t c)
{
  center_ = c;
}

void Rectangle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

double Rectangle::getArea() const
{
  return height_ * width_;
}

rectangle_t Rectangle::getFrameRect() const
{
 return {width_, height_, center_};
}
