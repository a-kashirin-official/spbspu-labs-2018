#include "circle.hpp"
#include <iostream>
#include <cmath>

Circle::Circle(const point_t & pos, const double radius):
  pos_(pos),
  radius_(radius)
{
  if(radius<0.0)
  {
    throw std::invalid_argument("Invalid radius");
  }
}

double Circle::getArea() const
{
  return M_PI*radius_*radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {pos_, 2.0*radius_, 2.0*radius_};
}

void Circle::move(const point_t & point)
{
  pos_=point;
}

void Circle::move(const double dx, const double dy)
{
  pos_.x+=dx;
  pos_.y+=dy;
}

void Circle::print(std::ostream & out) const
{
  out << "Circle: center: (" << pos_.x << "," << pos_.y << "), radius=" << radius_ << std::endl;
}
