#include "circle.hpp"

#include <cmath>
#include <stdexcept>

Circle::Circle(const point_t & new_coord, double new_radius):
  coord_(new_coord), radius_(new_radius)
{
  if (new_radius < 0.0) {
    radius_ = 0.0;
    throw std::invalid_argument("Radius must be > 0");
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {2 * radius_, 2 * radius_, coord_};
}

void Circle::move(double dx, double dy)
{
  coord_.x += dx;
  coord_.y += dy;
}

void Circle::move(const point_t & pos)
{
  coord_ = pos;
}
