#include "circle.hpp"
#include <stdexcept>
#include <math.h>

using namespace mordvintseva;

Circle::Circle(const double r, const point_t & c):
  radius_(r),
  center_(c)
{
  if (radius_ < 0.0) {
    throw std::invalid_argument("The radius of circle must be non-negative");
  };
}

double Circle::getArea() const
{
  return (M_PI * radius_ * radius_);
}

rectangle_t Circle::getFrameRect() const
{
  rectangle_t rectangle = { 2 * radius_, 2 * radius_, center_ };
  return rectangle;
}

void Circle::move(const point_t & point)
{
  center_ = point;
}

void Circle::move(const double dx, const double dy) 
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::scale(const double factor)
{
  if (factor >= 0.0) {
    radius_ *= factor;
  } else {
    throw std::invalid_argument("The scaling factor must be non-negative");
  };
}
