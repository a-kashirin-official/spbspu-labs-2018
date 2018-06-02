#define _USE_MATH_DEFINES
#include "circle.hpp"
#include <cmath>
#include <stdexcept>

Circle::Circle(double radius, const point_t &pos) :
  radius_(radius),
  center_(pos)
{
  if (radius <= 0) {
    throw std::invalid_argument("Error: Invalid argument: Radius for Circle must be > 0.");
  }
}

double Circle::getArea() const
{
  return M_PI * pow(radius_, 2);
}

rectangle_t Circle::getFrameRect() const
{
  return { radius_ * 2, radius_ * 2, center_ };
}

point_t Circle::move(const point_t &coords)
{
  center_ = coords;
  return coords;
}

point_t Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
  return center_;
}
