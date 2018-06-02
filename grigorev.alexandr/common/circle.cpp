#include "circle.hpp"
#include <cmath>
#include <iostream>

grigorev::Circle::Circle(const grigorev::point_t & center, const double radius):
  center_(center),
  r_(radius)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Error: Invalid radius");
  }
}

double grigorev::Circle::getArea() const
{
  return M_PI * r_ * r_;
}

grigorev::rectangle_t grigorev::Circle::getFrameRect() const
{
  return grigorev::rectangle_t{center_, 2*r_, 2*r_};
}

void grigorev::Circle::move(const grigorev::point_t & newCenter)
{
  center_ = newCenter;
}

void grigorev::Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void grigorev::Circle::scale(const double coef)
{
  if (coef < 0.0)
  {
    throw std::invalid_argument("Error: Invalid scale coef");
  }
  r_ *= coef;
}

void grigorev::Circle::rotate(const double /*angle*/)
{
}
