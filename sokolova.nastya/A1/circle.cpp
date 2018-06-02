#include "circle.hpp"

#include <iostream>
#include <cmath>
#include <stdexcept>


Circle::Circle(const point_t &centre, double radius) :
  radius_(radius)
{
  centre_=centre;
  if (radius < 0.0)
  {
    throw std::invalid_argument("Wrong radius!");
  }
}

double Circle::getArea() const
{
  return M_PI*radius_*radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {centre_, 2 * radius_, 2 * radius_ };
}

void Circle::move(const point_t & newcentre)
{
  centre_ = newcentre;
}

void Circle::move(double dx, double dy)
{
  centre_.x += dx;
  centre_.y += dy;
}

void Circle::scale(double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Wrong factor!");
  }
  radius_ *= factor;
}

