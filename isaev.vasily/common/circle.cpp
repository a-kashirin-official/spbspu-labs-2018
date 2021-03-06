#define _USE_MATH_DEFINES

#include "circle.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>

using namespace isaev;

Circle::Circle(const point_t &centre, double r) :
pos_(centre),
rad_(r)
{
  if(r < 0.0)
  {
    throw std::invalid_argument("Radius can't be negative");
  } //point is circle too
}
point_t Circle::getCenter() const
{
  return pos_;
}
double Circle::getRadius() const
{
  return rad_; 
}
double Circle::getArea() const
{
  return (rad_ * rad_ * M_PI);
}
rectangle_t Circle::getFrameRect() const
{
  return { pos_, rad_ * 2, rad_ * 2 };
}
void Circle::move(const point_t &point)
{
  pos_ = point;
}
void Circle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}
void Circle::scale(const double ratio)
{
  if(ratio < 0.0)
  {
    throw std::invalid_argument("Ratio can't be negative");
  }
  rad_ *= ratio;
}
void Circle::printShapeInfo() const
{
  std::cout << "Circle info:\n";
  std::cout << "Centre: {" << pos_.x << "," << pos_.y << "}\n";
  std::cout << "Radius = " << rad_ << "\n";
}

