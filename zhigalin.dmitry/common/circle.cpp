#include "circle.hpp"
#include <iostream>
#include <cmath>

zhigalin::Circle::Circle(const point_t & pos, const double radius):
  Shape(pos)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Radius must be positive!");
  }
  radius_ = radius;
};

zhigalin::rectangle_t zhigalin::Circle::getFrameRect() const
{
  return rectangle_t{2.0 * radius_, 2.0 * radius_, pos_};
};

double zhigalin::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
};

void zhigalin::Circle::move(const point_t & pos)
{
  pos_ = pos;
};

void zhigalin::Circle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
};

void zhigalin::Circle::scale(const double coeff)
{
  if (coeff <= 0.0)
  {
    throw std::invalid_argument("Scale coefficient must be positive!");
  }
  radius_ *= coeff;
};
