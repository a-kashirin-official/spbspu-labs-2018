#include "circle.hpp"
#include <iostream>
#include <cmath>

Circle::Circle(const double rad,const point_t &poss)
{
  if ( rad< 0.0)
  {
    throw std::invalid_argument("Radius must be nonnegative");
  }
  else
  radius_=rad;
  center_=poss;
}

double Circle::getArea() const
{
  return M_PI*radius_*radius_;
};

rectangle_t Circle::getFrameRect() const
{
  return { radius_ * 2, radius_ * 2, center_};
};

void Circle::move(const point_t &poss)
{
  center_ = poss;
};

void Circle::move(const double Ox, const double Oy)
{
  center_.x += Ox;
  center_.y += Oy;
};

void Circle::info() const
{
  std::cout <<"Radius: " << radius_ <<" Center of Circle: x = " << center_.x <<" y = " << center_.y << std::endl;
};

