#include "rectangle.hpp"

#include <iostream>

using std::cout;
using std::endl;

Rectangle::Rectangle(double h, double w, double x, double y) :
  height_(h),
  width_(w),     
  center_({x,y})
{
  if (h < 0 or w < 0)
  {
    throw std::invalid_argument("Width and height of the rectangle must be > 0");
  }
}

void Rectangle::printInfo() const
{
  cout << "--RECTANGLE--"<< endl;
  cout << "Area of rectangle is " << getArea() << endl;
  rectangle_t frec;
  frec = getFrameRect();
  cout << endl << "FRAME RECTANGLE" << endl << "Height: " << frec.height << endl;
  cout << "Width: " << frec.width << endl << "x, y cords: " << frec.pos.x << " " << frec.pos.y << endl;
  cout << endl << "Cords of center of rectangle: " << center_.x << " " << center_.y << endl << endl;
}

double Rectangle::getArea() const
{
  return height_*width_;
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

rectangle_t Rectangle::getFrameRect() const
{
  return {width_,height_,center_};
}
