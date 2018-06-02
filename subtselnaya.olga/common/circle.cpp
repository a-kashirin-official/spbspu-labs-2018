#include "circle.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

using namespace subtselnaya;

Circle::Circle(const point_t & center, const double radius):
  center_(center),
  radius_(radius)
{
  if (radius < 0.0) {
    throw std::invalid_argument("Error! Radius is wrong!");
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t {radius_ * 2, radius_ * 2, center_};
}

void Circle::move(const point_t & resPoint)
{
  center_ = resPoint;
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::scale(const double value)
{
  if (value < 0.0) {
    throw std::invalid_argument("Wrong value of scaling");
  }
  radius_ *= value;
}
