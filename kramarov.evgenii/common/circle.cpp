#include "circle.hpp"
#include <cmath>
#include <stdexcept>

using namespace kramarov;

Circle::Circle(const point_t & center, const double radius):
  center_(center),
  radius_(radius)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Invalid parameter");
  };
}

double Circle::getArea() const
{
  return M_PI*radius_*radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{center_, 2*radius_, 2*radius_};
}

void Circle::move (const point_t & newLocation)
{
  center_ = newLocation;
}

void Circle::move (const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::scale (const double scaleRate)
{
  if (scaleRate < 0.0)
  {
    throw std::invalid_argument ("Scale rate must be above 0");
  }
  radius_ *= scaleRate;
}

point_t kramarov::Circle::getXY() const
{
  return getFrameRect().pos;
}
