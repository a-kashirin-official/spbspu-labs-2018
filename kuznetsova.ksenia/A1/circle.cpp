#include "circle.hpp"
#include <iostream>
#include <cmath>

Circle::Circle(point_t &centre, double radius) :
centre_(centre)
{
  if (radius < 0) {
    radius_ = 0;
    std::cout << "Radius cannot be negative" << std::endl;
  }
  else{
    radius_ = radius;
  }
}
double Circle::getArea() const
{
  return M_PI * radius_*radius_;
}
rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{ centre_, 2 * radius_, 2 * radius_ };
}
void Circle::move(point_t &newcentre)
{
  centre_ = newcentre;
}
void Circle::move(double dx, double dy)
{
  centre_.x += dx;
  centre_.y += dy;
}
