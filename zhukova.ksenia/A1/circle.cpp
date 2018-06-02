#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

Circle::Circle(const point_t & center, const double radius):
  center_(center),
  radius_(radius)
{
  if (radius <= 0) {
    std::cerr << "Invalid parameter value" << std::endl;
  }
}

double Circle::getArea() const
{
  return M_PI * pow(radius_, 2);
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{ radius_ * 2, radius_ * 2, center_ };
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::move(const point_t & point)
{
  center_ = point;
}

void Circle::printParameters() const
{
  std::cout << "Circle radius is " << radius_ << std::endl;
  std::cout << "Circle center is in (" << center_.x << ", " << center_.y << ")" << std::endl <<  std::endl;
}
