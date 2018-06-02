#include "circle.hpp"

#include <iostream>
#include <cmath>

Circle::Circle(const double r, const point_t & p):
  radius_(r),
  pos_(p)
{
  if (radius_ < 0)
  {
    std::cerr << "Invalid_circle_radius";
  }
}

double Circle::getArea() const
{
  return  M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {2 * radius_, 2 * radius_, pos_};
}

void Circle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}

void Circle::move(const point_t & p)
{
  pos_ = p;
}

void Circle::printParameters() const
{
  std::cout << "Circle radius=" << radius_ << std::endl;
  std::cout << "Circle center (" << pos_.x << "," << pos_.y << ")" << std::endl;
}

void Circle::printCenter() const
{
  std::cout << " (" << pos_.x << "," << pos_.y << ")" << std::endl;
}
