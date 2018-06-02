#include "rectangle.hpp"

#include <iostream>

using namespace std;

Rectangle::Rectangle(double height, double width, double x, double y) :
  height_(height),
  width_(width),
  center_({x,y})
{
  if ( width < 0 or height < 0)
  {
    throw invalid_argument("Error: height or/and width > 0");
  }
}

double Rectangle::getArea() const {
  return height_*width_;
}

void Rectangle::move(point_t center) {
  center_ = center;
}

void Rectangle::move(double dx, double dy) {
  center_.x += dx;
  center_.y += dy;
}

rectangle_t Rectangle::getFrameRect() const {
  return {width_, height_, center_};
}

void Rectangle::writeInfoOfObject() const {
  cout<<"Rectangle information: " <<endl
    <<" Area: " <<getArea() <<endl
    <<" Frame:" <<endl
    <<"  Height: " <<getFrameRect().height <<endl
    <<"  Width:  " <<getFrameRect().width <<endl
    <<"  x, y cords: " <<getFrameRect().pos.x <<" " <<getFrameRect().pos.y <<endl
    <<" Center (x, y): (" <<center_.x <<", " <<center_.y <<")" <<endl;
}