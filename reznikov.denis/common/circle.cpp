#include "circle.hpp"
#include <iostream>
#include <cmath>

using namespace reznikov;

Circle::Circle(const double radius, const point_t &center) :
  radius_(radius),
  center_(center)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("Invalid circle radius. Radius must be above zero.");
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return{ 2.0 * radius_, 2.0 * radius_, center_ };
}

void Circle::move(const point_t &point)
{
  center_ = point;
}

void Circle::move(const double dx, const double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void Circle::scale(const double coefficient)
{
  if (coefficient < 0.0) {
    throw std::invalid_argument("Invalid scale coefficient. Scale coefficient must be above zero.");
  }
  else
  {
    radius_ *= coefficient;
  }
}

void Circle::inf() const
{
  std::cout << "Circle:" << std::endl;
  std::cout << "  Radius: " << radius_ << "  Position:" << std::endl;
  std::cout << "    x: " << center_.x << "   y: " << center_.y << std::endl;
  std::cout << "  Area: " << this->getArea() << std::endl;
}

double Circle::getRadius() const
{
  return radius_;
}

point_t Circle::getPosition() const 
{
  return center_;
}


