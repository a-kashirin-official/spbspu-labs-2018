#include "circle.hpp"
#include <cmath>
#include <cassert>

Circle::Circle(const point_t & pos, const double radius) :
  position_(pos),
  radius_(radius)
{
  assert (radius_ >= 0);
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {position_, radius_ * 2, radius_ * 2};
}

void Circle::move(const point_t & posTo)
{
  position_ = posTo;
}

void Circle::move(const double dx, const double dy)
{
  position_.x += dx;
  position_.y += dy;
}
