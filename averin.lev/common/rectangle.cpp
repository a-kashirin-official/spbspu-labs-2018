#include "rectangle.hpp"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;
using namespace averin;

Rectangle::Rectangle(double h, double w, double x, double y) :
  height_(h),
  width_(w),     
  center_({x,y}),
  angle_(0),
  topLeft_({x-w/2,y+h/2})
{
  if (h < 0.0 or w < 0.0)
  {
    throw std::invalid_argument("Width and height of the rectangle must be > 0");
  }
}

void Rectangle::printInfo() const
{
  cout << "--RECTANGLE--"<< endl;
  cout << "Angle: " << angle_ << endl;
  cout << "Area of rectangle is " << getArea() << endl;
  rectangle_t frec;
  frec = getFrameRect();
  cout << endl << "FRAME RECTANGLE" << endl << "Height: " << frec.height << endl;
  cout << "Width: " << frec.width << endl << "x, y cords: " << frec.pos.x << " " << frec.pos.y << endl;
  cout << endl << "Cords of center of rectangle: " << center_.x << " " << center_.y << endl;
  cout << endl << "Cords of left top corner. x: " << topLeft_.x << " y: " << topLeft_.y << endl << endl;
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

void Rectangle::scale(double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("ratio must be >= 0");
  }
  height_ *= ratio;
  width_ *= ratio;
}

double Rectangle::getHeight()
{
  return height_;
}

double Rectangle::getWidth()
{
  return width_;
}

void Rectangle::rotate(double deg)
{
  angle_ -= deg;
  if (angle_ < 0.0)
  {
    angle_ += 360.0;
  }
  while (angle_ > 360.0)
  {
    angle_ -= 360.0;
  }
    double x = center_.x;
    double y = center_.y;
    double x0 = topLeft_.x;
    double y0 = topLeft_.y;
    double degRad = deg * (M_PI/180);
    double rx = x0 - x;
    double ry = y0 - y;
    double c = cos(degRad);
    double s = sin(degRad);
    topLeft_.x = x + rx * c - ry * s;
    topLeft_.y = y + rx * s + ry * c;
}

void Rectangle::printAngle() const
{
  cout << angle_ << endl;
}

void Rectangle::setAngle(double deg) 
{
  angle_ = deg;
}

void Rectangle::printName() const
{
  cout << "Rectangle";
}
