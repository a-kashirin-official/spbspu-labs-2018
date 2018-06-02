#include "circle.hpp"

#include <stdexcept>
#include <math.h>

pichugina::Circle::Circle(const pichugina::point_t & centre, const double radius):
  centre_(centre),
  radius_(radius)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Invalid circle");
  }
}

double pichugina::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

pichugina::rectangle_t pichugina::Circle::getFrameRect() const
{
  return {centre_, 2 * radius_, 2 * radius_};
}

void pichugina::Circle::move(const pichugina::point_t & pos)
{
  centre_ = pos;
}

void pichugina::Circle::move(const double dx, const double dy)
{
  centre_.x += dx;
  centre_.y += dy;
}

void pichugina::Circle::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Invalid factor");
  }
  radius_ *= factor;
}
