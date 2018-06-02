#include "circle.hpp"
#include <cassert>
#include <cmath>

Circle::Circle(const point_t &center, const double radius):
  position_(center),
  radius_(radius)
{
  assert(radius >= 0);
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {2 * radius_, 2 * radius_, position_};
}

void Circle::move(const point_t &center)
{
  position_ = center;
}

void Circle::move(const double dx, const double dy)
{
  position_.x += dx;
  position_.y += dy;
}
