#include "circle.hpp"
#include <cmath>
#include <math.h>
#include <stdexcept>

using namespace lysenko;

Circle::Circle(const point_t & center,const double radius):
  center_(center),
  radius_(radius)

{
  if (radius_ < 0.0)
  {
    throw::std::invalid_argument("Error! Radius must be >= 0.0");
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{center_, 2 * radius_, 2 * radius_};
}

void Circle::move(const point_t & center)
{
  center_ = center;
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::scale(const double ScaleCoeff)
{
  if (ScaleCoeff < 0.0)
  {
    throw::std::invalid_argument("Error! ScaleCoeff must be >= 0.0");
  }
  radius_ *=ScaleCoeff;
}
