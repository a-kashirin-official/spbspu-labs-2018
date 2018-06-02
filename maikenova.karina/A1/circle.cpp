#include "circle.hpp"
#include <stdexcept>
#include <cmath>

Circle::Circle(const point_t & mid, const double radius):
  center_(mid),
  r_(radius)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Radius must be greater than 0.");
  }
}

double  Circle::getArea() const
{
  return M_PI*r_*r_;
}

rectangle_t Circle::getFrameRect() const
{
  return {2*r_, 2*r_, center_};
}

void Circle::move(const point_t & newPos)
{
  center_ = newPos;
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}
