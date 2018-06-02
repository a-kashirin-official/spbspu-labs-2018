#include <iostream>
#include <cmath>
#include "circle.hpp"

using namespace lebedev;

Circle::Circle(const point_t & center, const double radius):
  center_(center),
  radius_(radius)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Invalid radius.");
  }
}

double Circle::getArea() const
{
  return M_PI*radius_*radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{center_,2*radius_,2*radius_};
}

void Circle::move(const point_t & transferPoint)
{
  center_ = transferPoint;
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::scale(const double scaleFactor)
{
  if (scaleFactor < 0.0)
  {
    throw std::invalid_argument("Invalid scale factor.");
  }
  radius_ *= scaleFactor;
}

void Circle::printCurrentInfo() const
{
  std::cout << "Circle center (x,y): " << center_.x << ", " << center_.y << std::endl;
  std::cout << "Circle radius: " << radius_ << std::endl;
}
