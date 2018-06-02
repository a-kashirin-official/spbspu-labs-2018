#include "circle.hpp"
#include "base-types.hpp"
#include <iostream>
#include <math.h>
#include <stdexcept>

shapiev::Circle::Circle (const point_t & Ncenter,const double Nradius):
  center_(Ncenter),
  radius_(Nradius),
  angle_(0.0)
{
  if (Nradius < 0.0) {
    throw std::invalid_argument("Radius must be nonnegative");
  }
}

double shapiev::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

shapiev::rectangle_t shapiev::Circle::getFrameRect() const
{
  return rectangle_t { radius_ * 2, radius_ * 2, center_ } ;
}

void shapiev::Circle::move(const point_t & resPoint)
{
  center_ = resPoint;
}

void shapiev::Circle::move (const double dx, const double dy)
{
  center_.x+= dx;
  center_.y+= dy;
}

void shapiev::Circle::scale(double ratio)
{
  if (ratio < 0.0)
  {
    throw std::invalid_argument("Ratio must be positive");
  }
  radius_ *= ratio;
}

shapiev::point_t shapiev::Circle::getPos() const
{
  return center_;
}

double shapiev::Circle::getRadius() const
{
  return radius_;
}

void shapiev::Circle::rotate(const double angle)
{
  angle_ += angle;
  if (angle_ >= 360)
  {
    angle_ = fmod(angle_, 360.0);
  }
}

void shapiev::Circle::printCircle() const
{
  std::cout << "Circle has center in (" << center_.x << ", " << center_.y << ')' << std::endl;
  std::cout << "  Radius is " << radius_ << std::endl;
}
