#include "circle.hpp"
#include <cmath>
#include <iostream>

Circle::Circle(double r, const point_t &pos) :
  radius_(r),
  center_(pos)
{
  if (r <= 0) {
    std::cerr << "Radius of the circle must be > 0";
  }
  radius_ = r;
}

Circle::Circle(double x, double y, double r) :
  center_({x, y})
{
  if (r <= 0) {
    std::cerr << "Radius of the circle must be > 0";
  }
  radius_ = r;
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

void Circle::move(double Ox, double Oy)
{
  center_.x += Ox;
  center_.y += Oy;
}

void Circle::printInfo()
{
  std::cout << "CIRCLE:" << std::endl;
}
