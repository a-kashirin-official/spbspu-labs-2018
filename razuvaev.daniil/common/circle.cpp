#include "circle.hpp"
#include <iostream>
#include <cmath>

using namespace std;
using namespace razuvaev;

Circle::Circle(double radius, double x, double y) :
  radius_(radius), center_({x,y})
{
  if (radius < 0.0){
    throw std::invalid_argument("Error: Radius < 0!");
  }
}

double Circle::getArea() const {
  return radius_*radius_*M_PI;
}

rectangle_t Circle::getFrameRect() const {
  return {2*radius_, 2*radius_, center_};
}

void Circle::move(point_t center)
{
  center_ = center;
}

void Circle::move(double dx, double dy) {
  center_.x += dx;
  center_.y += dy;
}

void Circle::scale(double ratio){
  if(ratio<0.0){
    throw invalid_argument("Ratio < 0!");
  }else{
    radius_*=ratio;
  }
}

double Circle::getRadius() {
  return radius_;
}

double Circle::getHeight() {
  return radius_*2;
}

double Circle::getWidth() {
  return radius_*2;
}

void Circle::writeInfoOfObject() const
{
  cout<<"Circle information:" <<endl
    <<" Area of circle is " <<getArea() <<endl
    <<" Frame:" <<endl
    <<"  Height: " <<getFrameRect().height <<endl
    <<"  Width: " <<getFrameRect().width <<endl
    <<"  x, y cords: " <<getFrameRect().pos.x <<" " <<getFrameRect().pos.y <<endl
    <<" Center (x, y): (" <<center_.x <<", " <<center_.y <<")" <<endl;
}
