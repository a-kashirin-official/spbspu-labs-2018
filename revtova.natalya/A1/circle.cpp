#include "circle.hpp"
#include <cassert>
#include <cmath>

Circle::Circle(const point_t & pos, const double radius):
  pos_(pos),
  radius_(radius)
{
  assert(radius >= 0.0);
}
double Circle::getArea() const
{
  return M_PI*radius_*radius_;
}
rectangle_t Circle::getFrameRect() const
{
  return {radius_*2, radius_*2, pos_};
}
void Circle::move(const point_t & pos)
{
  pos_ = pos;
}
void Circle::move(double dx, double dy)
{
  pos_.x += dx;
  pos_.y += dy;
}
