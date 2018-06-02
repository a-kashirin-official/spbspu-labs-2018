#include "circle.hpp"
#include <cassert>
#include <math.h>
#include <iostream>

Circle::Circle(const point_t &point, const double radius):
  pos_(point),
  radius_(radius)
{
  assert(radius >= 0);
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  rectangle_t rectangle = {pos_, radius_ * 2, radius_ * 2};
  return rectangle;
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

void Circle::printInfo() const
{
  std::cout << "Coordinates: (" << pos_.x << "," << pos_.y << ")" << std::endl;
}
