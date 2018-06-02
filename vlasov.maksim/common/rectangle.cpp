#include "rectangle.hpp"
#include <iostream>

using namespace vlasov;

Rectangle::Rectangle(double _width, double _height, point_t _pos) :
  width(_width),
  height(_height)
{
  pos = _pos;
  if (height < 0.0 || width < 0.0) {
    throw std::invalid_argument("WARNING: invalid parameter of Rectangle\n");
  }
};

rectangle_t Rectangle::getFrameRect() const {
  return {pos, width, height};
}

double Rectangle::getArea() const {
  return width*height;
}

void Rectangle::scale(double _multiplier){
  if (_multiplier < 0.0){
    throw std::invalid_argument("WARNING: signed scaling is not suitable!\n");
  }
  width*=_multiplier;
  height*=_multiplier;
}
