#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdexcept>

using namespace konkin;

Circle::Circle(const point_t & centre, const double radius):
  centre_(centre),
  radius_(radius)
{
  if(radius < 0.0)
  {
    throw std::invalid_argument("Error. incorrect radius.");
  }
}

double Circle::getArea() const
{
  return(M_PI * radius_ * radius_);
}

rectangle_t Circle::getFrameRect() const
{
  return{2 * radius_, 2 * radius_, centre_};
}

void Circle::move(const double dx, const double dy)
{
  centre_.x += dx;
  centre_.y += dy;
}

void Circle::move(const point_t & pos)
{
  centre_ = pos;
}

void Circle::scale(const double coef)
{
  if (coef < 0.0)
  {
    throw std::invalid_argument("Error. incorrect parametr of scale.");
  }
  radius_ *= coef;
}
