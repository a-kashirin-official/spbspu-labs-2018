#include "circle.hpp"
#include <stdexcept>
#include <cmath>

using namespace kashirin;

Circle::Circle(double radius, const point_t &pos):
  radius_(radius),
  center_(pos)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("Invalid argument");
  }
}

double Circle::getArea() const
{
  return M_PI * pow(radius_, 2);
}

rectangle_t Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, center_};
}

point_t Circle::getCenter() const
{
  return center_;
}

void Circle::move(const point_t &newPoint)
{
  center_ = newPoint;
}

void Circle::move(const double dx,const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::scale(const double coef)
{
  if (coef <= 0)
  {
    throw std::invalid_argument("Invalid coef");
  }
  radius_ *= coef;
}
