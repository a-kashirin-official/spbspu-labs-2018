#define _USE_MATH_DEFINES

#include "circle.hpp"
#include <iostream>
#include <cmath>

Circle::Circle(const point_t &pos, const double radius) :
  pos_(pos),
  radius_(radius)
{
  if (radius_ <= 0.0)
  {
    std::cerr << "Invalid radius value." << std::endl;
  }
}

double Circle::getArea() const
{
  return (radius_ * radius_ * M_PI);
}

rectangle_t Circle::getFrameRect() const
{
  return { radius_ * 2, radius_ * 2, pos_ };
}

void Circle::showSize() const
{
  std::cout << "Radius of the circle: " << radius_ << std::endl;
}

void Circle::showPos() const
{
  std::cout << "Coordinates of the center of the circle ";
  std::cout << "X = " << pos_.x << " Y = " << pos_.y << std::endl;
}

void Circle::move(const point_t &pos)
{
  pos_ = pos;
}

void Circle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}
