#include "circle.hpp"
#include <iostream>
#include <cmath>

mironenkov::Circle::Circle(const point_t & pos, const double radius):
  Shape(pos)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Radius is Invalid!");
  }
  radius_ = radius;
};

mironenkov::rectangle_t mironenkov::Circle::getFrameRect() const
{
  return rectangle_t{2.0 * radius_, 2.0 * radius_, pos_};
};

double mironenkov::Circle::getArea() const
{
  return radius_ * radius_* M_PI;
};

void mironenkov::Circle::move(const point_t & pos)
{
  pos_ = pos;
};

void mironenkov::Circle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
};

void mironenkov::Circle::scale(const double coeff)
{
  if(coeff <= 0.0)
  {
    throw std::invalid_argument("Scale coeff is Invalid!");
  }
  radius_ *= coeff;
};
