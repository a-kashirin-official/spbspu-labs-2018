#include "circle.hpp"
#include <stdexcept>
#include <cmath>

maikenova::Circle::Circle(const point_t & center, const double radius):
  center_(center),
  r_(radius)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Radius must not be nagative.");
  }
}

double maikenova::Circle::getArea() const
{
  return M_PI*r_*r_;
}

maikenova::rectangle_t maikenova::Circle::getFrameRect() const
{
  return {2*r_, 2*r_, center_};
}

void maikenova::Circle::move(const point_t & newPos)
{
  center_ = newPos;
}

void maikenova::Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}
void maikenova::Circle::scale(const double ratio)
{
  if (ratio < 0)
  {
    throw std::invalid_argument("Ratio must not be negative");
  }
  r_ *= ratio;
}

maikenova::point_t maikenova::Circle::getPos() const
{
  return center_;
}

void maikenova::Circle::rotate(double)
{
}
