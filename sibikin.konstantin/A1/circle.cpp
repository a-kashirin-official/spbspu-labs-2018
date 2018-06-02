#include "circle.hpp"
#include <cmath>
#include <stdexcept>

Circle::Circle(const point_t & center, const double R):
  pos_(center),
  r_(R)
{
  if (R < 0.0)
  {
    throw std::invalid_argument("Radius can not be negative!");
  }
}

double Circle::getArea() const
{
  return r_ * r_ * M_PI;
}

rectangle_t Circle::getFrameRect() const
{
  return {2 * r_, 2 * r_, pos_};
}

void Circle::move(const point_t & newCenter)
{
  pos_ = newCenter;
}

void Circle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}
