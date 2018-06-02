#include "circle.hpp"

#include <stdexcept>
#include <cmath>
#include <iostream>

using namespace ponomarev;

Circle::Circle(const point_t &center, const double radius):
  position_(center),
  radius_(radius)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("invalid_radius, must be >= 0");
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {2.0 * radius_, 2.0 * radius_, position_};
}

void Circle::move(const point_t &center)
{
  position_ = center;
}

void Circle::move(const double dx, const double dy)
{
  position_.x += dx;
  position_.y += dy;
}

void Circle::scale(const double coefficient)
{
  if (coefficient < 0.0)
  {
    throw std::invalid_argument("invalid scaling coefficient");
  }
  radius_ *= coefficient;
}

void Circle::rotate(const double /*angle*/)
{
}

void Circle::printShape() const
{
  std::cout << "Circle";
}

