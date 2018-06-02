#include "circle.hpp"
#include <iostream>
#include <math.h>

kostylev::Circle::Circle(const point_t & mid, const double radius):
  mid_(mid),
  radius_(radius)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Error. Invalid height or width of rectangle.");
  }
}

double kostylev::Circle::getArea() const
{
  return 3.14 * radius_ * radius_;
}

kostylev::rectangle_t kostylev::Circle::getFrameRect() const
{
  return {mid_, 2 * radius_, 2 * radius_};
}

void kostylev::Circle::move(const point_t & point)
{
  mid_ = point;
}

void kostylev::Circle::move(const double dx, const double dy)
{
  mid_.x += dx;
  mid_.y += dy;
}

void kostylev::Circle::scale(const double coef)
{
  if (coef < 0.0)
  {
    throw std::invalid_argument("Error. Invalid parameter of scaling.");
  }
  radius_ *= coef;
}
