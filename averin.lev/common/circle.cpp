#include "circle.hpp"
#include <iostream>
#include <cmath>
using std::cout;
using std::endl;
using namespace averin;

Circle::Circle(double r, double x, double y) :
  rad_(r),
  center_({x,y}),
  angle_(0)
{
  if (r < 0.0)
  {  
    throw std::invalid_argument("Radius of the circle must be > 0");
  }
}

double Circle::getArea() const
{
  return rad_*rad_*M_PI;
}

rectangle_t Circle::getFrameRect() const
{
  return {2*rad_, 2*rad_, center_};
}

void Circle::move(point_t c)
{
  center_ = c;
}

void Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::printInfo() const
{
  cout << "--CIRCLE--"<< endl;
  cout << "Angle: " << angle_ << endl;
  cout << "Area of circle is " << getArea() << endl;
  rectangle_t frec;
  frec = getFrameRect();
  cout << endl << "FRAME RECTANGLE" << endl << "Height: " << frec.height << endl;
  cout << "Width: " << frec.width << endl << "x, y cords: " << frec.pos.x << " " << frec.pos.y << endl;
  cout << endl << "Cords of center of rectangle: " << center_.x << " " << center_.y << endl << endl;
}

void Circle::scale(double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("Ratio must be >= 0");
  }
  rad_ *= ratio;
}

double Circle::getRad()
{
  return rad_;
}

void Circle::rotate(double deg)
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
}

void Circle::printAngle() const
{
  cout << angle_ << endl;
}

void Circle::setAngle(double deg) 
{
  angle_ = deg;
}

void Circle::printName() const
{
  cout << "Circle";
}
