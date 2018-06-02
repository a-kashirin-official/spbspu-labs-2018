#include "circle.hpp"

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <stdexcept>

marchenko::Circle::Circle(const point_t &centerPos, const double radius) :
  center_(centerPos),
  radius_(radius)
{
  if (radius_ < 0.0)
  {
    throw std::invalid_argument("Invalid value of radius. It must be >=0.");
  }
}

double marchenko::Circle::getArea() const
{
  return radius_ * radius_ * M_PI;
}

marchenko::rectangle_t marchenko::Circle::getFrameRect() const
{
  return { radius_ * 2, radius_ * 2, center_ };
}

void marchenko::Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void marchenko::Circle::move(const point_t &newPos)
{
  center_ = newPos;
}

void marchenko::Circle::scale(const double coefficient)
{
  if (coefficient < 0.0)
  {
    throw std::invalid_argument("Invalid coefficient of scale. It must be >=0.");
  }
  else
  {
    radius_ *= coefficient;
  }
}
