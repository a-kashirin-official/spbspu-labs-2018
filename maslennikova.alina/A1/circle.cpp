#include <cmath>
#include "circle.hpp"
#include <stdexcept>
Circle::Circle(const point_t & center, double radius):
  pos(center),
  rad(radius)
{
  if (rad <= 0){
    throw std::invalid_argument("Invalid radius specified");
  }
}

double Circle::getArea() const{
  return rad * rad * M_PI;
}

rectangle_t Circle::getFrameRect() const{
  return {2*rad,2*rad,pos};
}

void Circle::move(const point_t & newCenter){
  pos = newCenter;
}

void Circle::move(const double dx, const double dy){
  pos.x += dx;
  pos.y += dy;
}
