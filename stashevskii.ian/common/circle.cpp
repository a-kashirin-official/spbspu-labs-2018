#include <iostream>
#include "circle.hpp"
#include <cmath>

using namespace stashevskii;

Circle::Circle(const double radius, const point_t& point):
  angle_(0),
  radius_(radius),
  pos(point)
{
  if (radius < 0.0)
  {
    throw std::invalid_argument("Radius must be > 0");
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

void stashevskii::Circle::scale(double k)
{
  if (k < 0)
  {
    throw std::invalid_argument("Invalid scale argument");
  }
  else
  {
    radius_ *= k;
  }
}

void Circle::rotate (const double angle) 
{
  angle_=angle;
}

void Circle::printf() const
{
  std::cout << "Circle:" << std::endl;
  std::cout << " Radius: " << radius_ << " Position:";
  std::cout << "  x: " << pos.x << " y: " << pos.y << std::endl;
  std::cout << " Area: " << Circle::getArea() << std::endl;
}

point_t Circle::getPosition() const 
{
  return pos;
}
