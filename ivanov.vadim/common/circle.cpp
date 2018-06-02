#include "circle.hpp"
#include <cmath>
#include <stdexcept>

ivanov::Circle::Circle(const point_t & pos, double radius):
  centr_(pos),
  rad_(radius)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument ("ERROR");
  }
}

ivanov::rectangle_t ivanov::Circle::getFrameRect() const
{
  return {centr_, rad_ * 2, rad_ * 2};
}

double ivanov::Circle::getArea() const
{
  return rad_ * M_PI *rad_;
}

void ivanov::Circle::move(const point_t & posit)
{
  centr_ = posit;
}

void ivanov::Circle::move(double dx, double dy)
{
  centr_.x += dx;
  centr_.y += dy;
}

void ivanov::Circle::scale(double k)
{
  if (k < 0.0)
  {
    throw std::invalid_argument ("ERROR");
  }
  rad_ *= k;
}
