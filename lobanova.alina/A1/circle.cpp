
#include "circle.hpp"
#include <cmath>
#include <iostream>

Circle::Circle(const point_t &centre, const double rad) : centre_(centre), rad_(rad)
{
  if (rad <= 0) {
    std::cerr << "Radius is incorrect:  " << rad << ". Must be positive." << std::endl;
  }
}

rectangle_t Circle::getFrameRect() const
{
  return {centre_, rad_ * 2, rad_ * 2};
}

double Circle::getArea() const
{
  return rad_ * rad_ * M_PI;
}

void Circle::move(const point_t &a)
{
  centre_ = a;
}

void Circle::move(double dx, double dy)
{
  centre_.x += dx;
  centre_.y += dy;
}
