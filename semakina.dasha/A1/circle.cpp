#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

Circle::Circle(const point_t & center, const double radius):
  pos_(center),
  radius_(radius)
{
  if (radius_ <= 0)
  {
    std::cerr << "Invalid circle's radius" << std::endl;
  }
}

void Circle::output() const
{
  std::cout << "Coordinates of circle center (" << pos_.x << "," << pos_.y << ")" << std::endl;
}

void Circle::move(const point_t & pos)
{
  pos_ = pos;
}

void Circle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {2*radius_, 2*radius_, pos_};
}
