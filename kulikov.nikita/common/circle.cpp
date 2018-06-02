#include "circle.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

kulikov::Circle::Circle(const point_t & center, double r):
  center_(center),
  radius_(r)
{
  if (r < 0.0)
  {
    throw std::invalid_argument("Raduis can`t be negative");
  }
}

double kulikov::Circle::getArea() const
{
  return M_PI*(radius_*radius_);
}

kulikov::rectangle_t kulikov::Circle::getFrameRect() const
{
  return rectangle_t{center_, radius_*2, radius_*2};
}

void kulikov::Circle::move (const point_t & movement)
{
  center_ = movement;
}

void kulikov::Circle::move (double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void kulikov::Circle::scale (double koeff)
{
  if (koeff < 0.0)
  {
    throw std::invalid_argument("Negative koefficient");
  }
  radius_ *= koeff;
}
