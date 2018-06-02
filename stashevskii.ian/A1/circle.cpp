#include <iostream>
#include "circle.hpp"
#include <cmath>

Circle::Circle(const double radius, const point_t& point):
  radius_(radius),
  pos(point)
{
  if (radius < 0.0)
  {
    std::cerr << "Radius must be > 0" << std::endl;
  }
}

rectangle_t Circle::getFrameRect() const
{
  return{ 2*radius_, 2*radius_, pos};
}

double Circle::getArea() const
{
  return(radius_*radius_*M_PI);
}

void Circle::move(const double dx, const double dy)
{
  pos.x += dx;
  pos.y += dy;
}

void Circle::move(const point_t &point)
{
  pos.x = point.x;
  pos.y = point.y;
}
void Circle::printf() const
{
  std::cout << "Circle:" << std::endl;
  std::cout << "  Radius: " << radius_ << "  Position:";
  std::cout << "    x: " << pos.x << "   y: " << pos.y << std::endl;
  std::cout << "  Area: " << Circle::getArea() << std::endl;
}
