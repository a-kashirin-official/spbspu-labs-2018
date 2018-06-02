#define _USE_MATH_DEFINES
#include "circle.hpp"
#include <cmath>

usov::Circle::Circle(double radius, const point_t &center) :
  radius_(radius),
  center_(center)
{
  if (radius_ < 0.0)
  {
    throw std::invalid_argument("Radius could be > 0.0");
  }
}

double usov::Circle::getRadius() const
{
  return radius_;
}

double usov::Circle::getArea() const
{
  return(M_PI *radius_ * radius_);
}

usov::rectangle_t usov::Circle::getFrameRect() const
{
  return{ 2 * radius_,2 * radius_,center_ };
}

void usov::Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void usov::Circle::move(const point_t &center)
{
  center_ = center;
}

void usov::Circle::scale(double dscale)
{
  if (dscale < 0.0)
  {
    throw std::invalid_argument("Scale could be > 0.0");
  }
  radius_ *= dscale;
}

void usov::Circle::print() const
{
  std::cout << "Circle info: " << std::endl;
  std::cout << "center: " << center_.x << " " << center_.y << std::endl;
  std::cout << "radius: " << radius_ << std::endl;
  std::cout << std::endl;
}
