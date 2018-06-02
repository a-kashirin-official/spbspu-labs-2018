#include "circle.hpp"
#include <cmath>

Circle::Circle(const point_t & pos, double rad):
  center_(pos),
  radius_(rad)
{
  if (rad < 0)
  {
    throw IncorrectDataException();
  }
}

void Circle::move(const point_t & pos)
{
  center_ = pos;
}

void Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return { center_, 2 * radius_, 2 * radius_};
}
