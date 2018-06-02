#include "circle.hpp"
#include <iostream>
#include <cmath>

Circle::Circle(const point_t & pos, const double radius):
  Shape(pos)
{
  if (radius < 0)
  {
    throw std::invalid_argument("Radius must be positive!");
  }
  radius_ = radius;
};

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{2.0 * radius_, 2.0 * radius_, pos_};
};

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
};

void Circle::move(const point_t & pos)
{
  pos_ = pos;
};

void Circle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
};
