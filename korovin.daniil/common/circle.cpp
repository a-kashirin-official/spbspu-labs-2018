#include <cmath>
#include <iostream>
#include "circle.hpp"
using namespace korovin;
Circle::Circle(const point_t & center,const double radius):
  center_(center),
  radius_(radius)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("Invalid circle radius. Radius must be above zero.");
  }
}


double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{center_, 2*radius_, 2*radius_};
}

void Circle::move(const point_t & newCenter)
{
  center_ = newCenter;
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::scale(const double coefficient)
{
  if (coefficient < 0.0) {
    throw std::invalid_argument("Invalid scale coefficient.");
  }
  else
  {
    radius_ *= coefficient;
  }
}

double Circle::getRadius() const
{
  return radius_;
}

point_t Circle::getPos() const 
{
  return center_;
}
