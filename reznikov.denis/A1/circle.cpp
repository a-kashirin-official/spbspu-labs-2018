#include "circle.hpp"
#include <iostream>
#include <cmath>

Circle::Circle(const double radius, const point_t &center) :
  radius_(radius),
  center_(center)
{
  if (radius < 0.0)
  {
    std::cerr << "Radius must be > 0" << std::endl;
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

void Circle::inf() const
{
  std::cout << "Circle:" << std::endl;
  std::cout << "  Radius: " << radius_ << "  Position:";
  std::cout << "    x: " << center_.x << "   y: " << center_.y << std::endl;
  std::cout << "  Area: " << this->getArea() << std::endl;
}
