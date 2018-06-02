#include <cmath>
#include <cassert>
#include <iostream>
#include "circle.hpp"

Circle::Circle(const point_t &position, const double radius):
  pos_(position),
  radius_(radius)
{
  assert(radius>0);
}

void Circle::printInformation() const
{
  std::cout << "Coordinates - (" << pos_.x
            << ", " << pos_.y << ")\n";
}

double Circle::getArea() const
{
  return(M_PI * radius_ * radius_);
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

rectangle_t Circle::getFrameRect() const
{
  return {pos_, 2 * radius_, 2 * radius_};
}

