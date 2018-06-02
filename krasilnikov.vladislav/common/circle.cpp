#include "circle.hpp"

#include <iostream>
#include <stdexcept>
#include <math.h>

using namespace krasilnikov;

krasilnikov::Circle::Circle(const point_t & center, const double radius):
  center_(center),
  radius_(radius),
  angle_(0.0)
{
  if (radius_ < 0.0)
  {
    throw std::invalid_argument("Incorrect radius value");
  }
}

double krasilnikov::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t krasilnikov::Circle::getFrameRect() const
{
  return { 2 * radius_, 2 * radius_, center_ };
}

void krasilnikov::Circle::move(const point_t & newPosition)
{
  center_ = newPosition;
}

void krasilnikov::Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

point_t krasilnikov::Circle::getPosition() const
{
  return center_;
}

double krasilnikov::Circle::getRadius() const
{
  return radius_;
}

void krasilnikov::Circle::scale(const double factor)
{
  if (factor < 0.0)
  {
    throw std::invalid_argument("Invalid factor");
  }
  radius_ *= factor;
}

void krasilnikov::Circle::rotate(const double angle)
{
  angle_ += angle;
  if (angle_ >= 360)
  {
    angle_ = fmod(angle_, 360.0);
  }
}
