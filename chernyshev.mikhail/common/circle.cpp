#include "circle.hpp"
#include <iostream>
#include <cassert>
#include <cmath>

chernyshev::Circle::Circle(double r,point_t c):
  rad_(r),
  center_(c)        
{
  if (r < 0.0)
  {
    throw std::invalid_argument("Radius must be >=0");
  }
}

double chernyshev::Circle::getArea()const
{
  return M_PI*rad_*rad_;
}

chernyshev::rectangle_t chernyshev::Circle::getFrameRect()const
{
  return rectangle_t{2*rad_,2*rad_,center_};
}

void chernyshev::Circle::Move(double delta_x,double delta_y)
{
  center_.x += delta_x;
  center_.y += delta_y;
}
void chernyshev::Circle::Move(point_t newPoint)
{
  center_ = newPoint;
}

void chernyshev::Circle::scale(double size)
{
  if (size < 0.0)
  {
    throw std::invalid_argument("Koeff must be >=0");
  }
  rad_ *= size;
}

void chernyshev::Circle::printScale() const
{
  std::cout<<"Scale. Radius is "<<rad_<<std::endl;
}
