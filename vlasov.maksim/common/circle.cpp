#include "circle.hpp"
#include <iostream>
#include <cmath>

using namespace vlasov;

Circle::Circle(double _radius, point_t _pos) :
  radius(_radius)
{
  pos = _pos; //using point_t Shape::pos
  if (radius < 0.0) {
    throw std::invalid_argument ("WARNING: invalid parameter of Circle\n");
  }
}

double Circle::getArea() const {
  return radius*radius*M_PI;
}

rectangle_t Circle::getFrameRect() const {
  return{pos, 2 * radius, 2 * radius};
}

void Circle::scale(double _multiplier) {
  if (_multiplier< 0.0){
    throw std::invalid_argument("WARNING: signed scaling is not suitable!\n");
  }
  radius*=_multiplier;
}
