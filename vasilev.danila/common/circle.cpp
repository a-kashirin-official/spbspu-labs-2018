#define _USE_MATH_DEFINES_
#include <iostream>
#include <cmath>
#include <stdexcept>
#include "circle.hpp"
namespace vasilev
{
Circle::Circle(double radius, const point_t &center_point):
  r_(radius),
  circle_center_(center_point)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Radius can't be lower that 0");
  }
}
double Circle::getArea() const
{
  return (M_PI*r_*r_);
}
void Circle::getInfo() const
{
  std::cout << std::endl << "Radius: " << r_ << std::endl;
  std::cout << "Area: " << getArea() << std::endl;
  std::cout << "Point(x, y): (" << circle_center_.x << ", " << circle_center_.y << ")" << std::endl;
  std::cout << "Frame rectangle(h,w,center(x,y)): " << getFrameRect().height << ", " << getFrameRect().width
      <<", ("<<getFrameRect().pos.x<<", "<<getFrameRect().pos.y<<")"<<std::endl;
}
rectangle_t Circle::getFrameRect() const
{
  return {2*r_, 2*r_, circle_center_};
}
void Circle::move(const double dx, const double dy)
{
  circle_center_.x += dx;
  circle_center_.y += dy;
}
void Circle::move(const point_t &point)
{
  circle_center_ = point;
}
void Circle::scale(const double mult)
{
  if (mult < 0.0)
  {
    throw std::invalid_argument("INVALID_MULTIPLIER");
  }
  else
  {
    r_ *= mult;
  }
}
double Circle::getRadius()
{
  return r_;
}
}
