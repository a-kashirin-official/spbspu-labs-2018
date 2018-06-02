#define _USE_MATH_DEFINES
#include <cassert>
#include <cmath>
#include "circle.hpp"

Circle::Circle(const point_t &position, const double &radius) :
  radius_(radius),
  currPos_(position)
{
  assert(radius_ > 0.0);
}

void Circle::move(const point_t &newP)
{
  currPos_ = newP;
}

void Circle::move(const double &nX, const double &nY)
{
  currPos_.x += nX;
  currPos_.y += nY;
}

double Circle::getArea() const
{
  return radius_ * radius_ * M_PI;
}

rectangle_t Circle::getFrameRect() const
{
  return {currPos_, 2 * radius_, 2 * radius_};
}
