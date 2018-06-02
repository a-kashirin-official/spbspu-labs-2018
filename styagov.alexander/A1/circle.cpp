#include "circle.hpp"

#include <stdexcept>
#include <cmath>

Circle::Circle(const point_t & pos, const double radius):
  pos_(pos),
  radius_(radius)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Circle: Radius must be non-negative");
  }
}

double Circle::getRadius() const
{
  return radius_;
}

point_t Circle::getPos() const
{
  return pos_;
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return { pos_, radius_ * 2, radius_ * 2 };
}

void Circle::move(const point_t & pos)
{
  pos_ = pos;
}

void Circle::move(const double dx, const double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}
