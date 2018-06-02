#include "circle.hpp"
#include <cmath>
#include <iostream>

turkin::Circle::Circle(double r, const point_t &pos) :
  radius_(r),
  center_(pos)
{
  if (r <= 0) {
    throw std::invalid_argument("Radius of the circle must be > 0");
  }
  radius_ = r;
}

double turkin::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

turkin::rectangle_t turkin::Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, center_};
}

void turkin::Circle::move(const point_t &pos)
{
  center_ = pos;
}

void turkin::Circle::move(double Ox, double Oy)
{
  center_.x += Ox;
  center_.y += Oy;
}
void turkin::Circle::printInfo()
{
  std::cout << "CIRCLE:" << std::endl;
}

void turkin::Circle::scale(double k)
{
  if (k < 0) {
    throw std::invalid_argument("K > 0!");
  }
  radius_ *= k;
}

void turkin::Circle::rotate(double /*angle*/)
{

}

turkin::point_t turkin::Circle::getCenter() const
{
  return center_;
}


