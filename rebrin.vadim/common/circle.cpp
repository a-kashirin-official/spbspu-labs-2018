#include <stdexcept>
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "circle.hpp"


rebrin::Circle::Circle(const point_t& pos, double rad) : center_(pos), radius_(rad)
{
  if (rad < 0.0)
  {
    throw std::invalid_argument("Radius must be >= 0");
  }
}

double rebrin::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rebrin::rectangle_t rebrin::Circle::getFrameRect() const
{
  rectangle_t tmp{};
  tmp.pos.x = center_.x;
  tmp.pos.y = center_.y;
  tmp.width = 2 * radius_;
  tmp.height = 2 * radius_;
  return tmp;
}

void rebrin::Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void rebrin::Circle::move(const point_t& pos)
{
  center_ = pos;
}

void rebrin::Circle::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Factor must be >= 0");
  }

  radius_ *= factor;
}
