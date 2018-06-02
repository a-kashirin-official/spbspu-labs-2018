#include "circle.hpp"
#include <cmath>
#include <stdexcept>

Circle::Circle(const point_t &centre, double radius) :
  centre_(centre),
  radius_(radius)
{
  if (radius_ < 0.0)
  {
    radius_ = 0.0;
    std::invalid_argument("err, radius can`t be < 0 ");
  }
}

double Circle::getArea() const noexcept
{
  return M_PI*radius_*radius_;
}

rectangle_t Circle::getFrameRect() const noexcept
{
  return {centre_, 2 * radius_, 2 * radius_};
}

void Circle::move(const double dx, const double dy) noexcept
{
  centre_.x += dx;
  centre_.y += dy;
}

void Circle::move(const point_t &newcentre) noexcept
{
  centre_ = newcentre;
}

