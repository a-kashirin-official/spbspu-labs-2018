#include "circle.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>
#define _USE_MATH_DEFINES

Circle::Circle(const point_t &centre, double r):
pos_(centre),
rad_(r)
{
  if(r < 0.0)
  {
    throw std::invalid_argument("Radius can't be negative");
  } //if r=0, point, still works
}
rectangle_t Circle::getFrameRect() const
{
  return { rad_ * 2 , rad_ * 2, pos_ };
}
double Circle::getArea() const
{
  return (rad_ * rad_ * M_PI);
}
void Circle::move(const point_t &point)
{  
  pos_ = point;
}
void Circle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}
void Circle::printShapeInfo() const
{
  std::cout << "Circle inf:\n";
  std::cout << "Middle: [" << pos_.x << "," << pos_.y << "]\n";
  std::cout << "Rad = " << rad_ << "\n";
}

