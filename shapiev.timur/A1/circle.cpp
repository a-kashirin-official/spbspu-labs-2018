#include "circle.hpp"
#include <iostream>
#include <cmath>
#include <assert.h>

Circle::Circle (const point_t & Ncenter,const double Nradius):
  center_(Ncenter),
  radius_(Nradius)
{
  assert(Nradius >= 0);
}

double Circle::getArea() const {
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const {
  return rectangle_t { radius_ * 2, radius_ * 2, center_ } ;
}

void Circle::move(const point_t & resPoint){
  center_ = resPoint;
}

void Circle::move (const double dx, const double dy){
  center_.x+= dx;
  center_.y+= dy;
}

void Circle::printCircle() const {
  std::cout << "Circle has center in (" << center_.x << ", " << center_.y << ')' << std::endl;
  std::cout << "  Radius is " << radius_ << std::endl;
}

