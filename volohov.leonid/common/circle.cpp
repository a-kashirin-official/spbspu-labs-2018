#include <iostream>
#include <cmath>
#include "circle.hpp"

using namespace volohov;

Circle::Circle(const point_t & center, const double r):
  center_(center),
  r_(r)
{
  if (r_ < 0.0)
  {
    throw std::invalid_argument("Wait. Invalid radius of circle.");
  }
}

double Circle::getArea() const
{
  return M_PI * r_ * r_;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{center_, 2 * r_, 2 * r_};
}

void Circle::scale(const double coeff)
{
  if (coeff < 0.0)
  {
    throw std::invalid_argument("Wait. Invalid coefficient.");
  }
  r_ *= coeff;
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
