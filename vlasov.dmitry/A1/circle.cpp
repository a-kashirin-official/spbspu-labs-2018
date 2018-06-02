#include "circle.hpp"

#include <iostream>
#include <cmath>

Circle::Circle(const double rad, const point_t &poss):
  radius_(rad),
  center_(poss)
{
  if (radius_< 0.0)
  {
    throw std::invalid_argument("Check that radius is a positive number");
  }
};

double Circle::getArea() const
{
  return M_PI*radius_*radius_;
};

rectangle_t Circle::getFrameRect() const
{
  return { radius_*2, radius_*2, center_};
};

void Circle::move(const point_t &poss)
{
  center_=poss;
};

void Circle::move(const double xOffset, const double yOffset)
{
  center_.x += xOffset;
  center_.y += yOffset;
};
