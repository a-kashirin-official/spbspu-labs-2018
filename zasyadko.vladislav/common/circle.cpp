#include <iostream>
#include <stdexcept>
#include "circle.hpp"

#define _USE_MATH_DEFINES

#include <cmath>

using namespace zasyadko;

Circle::Circle(const point_t & center, const double radius):
  cntr_(center),
  r_(radius)
{
  if (r_ < 0.0)
  {
    throw std::invalid_argument("Invalid Parameters");
  }
}
  
void Circle::print() const
{
  std::cout << "Circle center:" << cntr_.x << "; " << cntr_.y << std::endl;
  std::cout << "Radius:" << r_ << std::endl;
  std::cout << "Get Area:" << getArea() << std::endl;
  std::cout << "Get frame width:" << getFrameRect().height << std::endl;
  std::cout << "Get frame height:" << getFrameRect().width << std::endl;
}

void Circle::move(const point_t & Center)
{
  cntr_ = Center;
}

void Circle::move(const double add_x, const double add_y)
{
  cntr_.x += add_x;
  cntr_.y += add_y;
}

double Circle::getArea() const
{
  return M_PI*r_*r_;
}

double Circle::getRadius() const
{
  return r_;
}

rectangle_t Circle::getFrameRect() const
{
  return {cntr_,2*r_,2*r_};
}
  
void Circle::scale(const double factor)
{
  if(factor < 0.0)
  {
    throw std::invalid_argument("INVALID FACTOR");
  }
  else
  {
    r_ *= factor;
  }
}
