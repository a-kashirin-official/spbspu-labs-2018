#include "circle.hpp"
#include <cmath>
#include <iostream>

Circle::Circle(double radius, const point_t & center) :
  radius_(radius),
  center_(center)
{
  if ((radius_ < 0)) {
    std::cerr << "Invalid circle radius" << std::endl;
  }
}

Circle::Circle(double radius, double x, double y) :
  radius_(radius)
{
  center_.x = x;
  center_.y = y;
  if ((radius_ < 0)) {
    std::cerr << "Invalid circle radius" << std::endl;
  }
}

double Circle::getArea() const
{
  return radius_ * radius_ * M_PI;
}

rectangle_t Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, {center_.x, center_.y}};
}

void Circle::move(const point_t & center)
{
  center_ = center;
}

void Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::printInfo() const
{
  std::cout << "It is circle" << '\n';
  std::cout << "Radius: " << radius_ << '\n';
  std::cout << "Center: ";
  std::cout << "x = " << center_.x << ", y = " << center_.y << '\n' << std::endl;
}
