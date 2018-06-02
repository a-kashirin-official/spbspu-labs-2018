#include "circle.hpp"
#include <cmath>
#include <iostream>

using namespace tseptsov;

Circle::Circle(const double rad, const point_t &pos) :
  radius_(rad),
  center_(pos)
{
  if (rad < 0.0) {
    throw std::invalid_argument("Radius of the circle must be > 0");
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, center_};
}

void Circle::move(const point_t &pos)
{
  center_ = pos;
}

void Circle::move(const double Ox, const double Oy)
{
  center_.x += Ox;
  center_.y += Oy;
}

void Circle::OutData() const
{
  std::cout << "Radius: " << radius_ << std::endl;
  std::cout << "Spot of middle on Ox = " << center_.x << std::endl;
  std::cout << "Spot of middle on Oy = " << center_.y << std::endl << std::endl;
}

void Circle::scale(double coef)
{
  if (coef < 0.0) {
    throw std::invalid_argument("Coef must be >0");
  }
  radius_ *= coef;
}

void Circle::rotate(double deg)
{
  deg += 0;
}

point_t Circle::getCenter() const
{
  return center_;
}


