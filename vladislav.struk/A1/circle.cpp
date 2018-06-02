#include "circle.hpp"
#include <cmath>
#include <stdexcept>

Circle::Circle(const point_t &pos, double radius):
pos_(pos),
radius_(radius)
{
  if (radius_ < 0.0)
  {
    throw std::invalid_argument("Wrong radius");
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {pos_.x,pos_.y, 2*radius_ , 2*radius_};
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

