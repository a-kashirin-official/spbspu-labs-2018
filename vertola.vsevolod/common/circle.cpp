#include "circle.hpp"
#include <stdexcept>
#include <math.h>

using namespace vertola;

Circle::Circle(const double r, const point_t & c):
  radius_(r),
  center_(c)
{
  if (r < 0.0)
  {
    throw std::invalid_argument("Radius < 0.0");
  }
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

void Circle::scale(const double scf)
{
  if (scf < 0.0){
    throw std::invalid_argument("scale Value < 0.0");
  }
  radius_ *=scf;
}
