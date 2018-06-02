#define _USE_MATH_DEFINES
#include "circle.hpp"
#include <cmath>
Circle::Circle(double radius, const point_t &center) :
  radius_(radius),
  center_(center)
{}

double Circle::getArea() const
{
  return(M_PI *radius_ * radius_);
}

rectangle_t Circle::getFrameRect() const
{
  return{ 2 * radius_,2 * radius_,center_ };
}

void Circle::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::move(const point_t &center)
{
  center_ = center;
}

void Circle::print() const
{
  std::cout << "Circle info: " << std::endl;
  std::cout << "center: " << center_.x << " " << center_.y << std::endl;
}
