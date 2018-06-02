#include "circle.hpp"

#include <stdexcept>
#include <cmath>

Circle::Circle(const point_t & pos, const double radius):
  pos_(pos),
  radius_(radius)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Radius must be > 0");
  }
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
