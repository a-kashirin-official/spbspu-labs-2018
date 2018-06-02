#include "circle.hpp"

#include <math.h>
#include <iostream>

Circle::Circle(const point_t & centre, const double radius):
  centre_(centre),
  radius_(radius)
  
{
  if(radius < 0)
  {
    std::cerr << "Error. incorrect radius" << std::endl;
  }

}

double Circle::getArea() const
{
  return(M_PI * radius_ * radius_);
}

rectangle_t Circle::getFrameRect() const
{
  return{2 * radius_, 2 * radius_, centre_};
}

void Circle::move(const double dx, const double dy)
{
  centre_.x += dx;
  centre_.y += dy;
}

void Circle::move(const point_t & pos)
{
  centre_ = pos;
}
