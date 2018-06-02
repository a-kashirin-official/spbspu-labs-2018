#include "circle.hpp"
#include <cmath>
#include <stdexcept>

Circle::Circle(const point_t & set_coordinate, double set_r) :
center_(set_coordinate), r_(set_r)
{
  if (r_ < 0.0)
  {
    r_ = 0.0;
    throw std::invalid_argument("Error, radius can't be < 0 ");
  }
}

double Circle::getArea() const
{
  return (M_PI * r_ * r_);
}

rectangle_t Circle::getFrameRect() const
{
  return {center_, r_ * 2, r_ * 2};
}

void Circle::move(const point_t & new_center)
{
  center_ = new_center;
}

void Circle::move(const double x_, const double y_)
{
  center_.x += x_;
  center_.y += y_;
}
