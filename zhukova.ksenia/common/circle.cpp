
#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdexcept>

zhukova::Circle::Circle(const zhukova::point_t & center, double radius):
  center_(center),
  radius_(radius),
  angle_(0)
{
  if (radius <= 0) {
    throw std::invalid_argument("Circle: Invalid radius value, constructor");
  }
}

zhukova::Circle::Circle(const zhukova::Circle & arg): 
  center_(arg.center_),
  radius_(arg.radius_),
  angle_(0)
{
  if (arg.radius_ <= 0) {
    throw std::invalid_argument("Circle: Invalid radius value, copy constructor");
  }
}

double zhukova::Circle::getArea() const
{
  return M_PI * pow(radius_, 2);
}

zhukova::rectangle_t zhukova::Circle::getFrameRect() const
{
  return zhukova::rectangle_t{ radius_ * 2, radius_ * 2, center_ };
}

void zhukova::Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void zhukova::Circle::move(const zhukova::point_t & point)
{
  center_ = point;
}

void zhukova::Circle::scale(double coefficient)
{
  if (coefficient < 0) {
    throw std::invalid_argument("Circle: Invalid scaling factor");
  }
  radius_ *= coefficient;
}

void zhukova::Circle::rotate(double deg)
{
  angle_ += deg;
}
