#include "circle.hpp"

#include <stdexcept>
#include <math.h>

suslov::Circle::Circle(const suslov::point_t & center, const double radius) :
  center_(center),
  radius_(radius),
  angle_(0.0)
  
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Invalid radius");
  }
}

double suslov::Circle::getArea() const noexcept
{
  return M_PI * pow(radius_, 2);
}

suslov::rectangle_t suslov::Circle::getFrameRect() const noexcept
{ 
  return { center_, 2 * radius_, 2 * radius_ };
}

double suslov::Circle::getAngle() const noexcept
{
  return angle_;
}

void suslov::Circle::move(const double dx, const double dy) noexcept
{
  center_.x += dx;
  center_.y += dy;
}

void suslov::Circle::move(const suslov::point_t & newPoint) noexcept
{
  center_ = newPoint;
}

void suslov::Circle::scale(const double coef)
{
  if (coef < 0.0)
  {
    throw std::invalid_argument("Invalid coefficient");
  }
  else
  {
    radius_ *= coef;
  }
}

void suslov::Circle::rotate(const double angle) noexcept
{
  angle_ += angle;
}
