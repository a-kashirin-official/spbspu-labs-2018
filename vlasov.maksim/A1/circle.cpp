#include "circle.hpp"
#include <iostream>
#include <cmath>

Circle::Circle(double _radius, point_t _pos) :
  Shape(_pos),
  radius(_radius)
{
  pos = _pos; //using point_t Shape::pos
  if (radius >= 0.0) {
    std::cout << "Circle constructed" << std::endl;
  } else {
    std::cerr << "Inaccessible area and frame: wrong radius" << std::endl;
    confirm = false;
  };
}

double Circle::getArea() const {
  if (confirm !=0) {
    std::cout << "circle's area ";
    return radius*radius*M_PI;
  } else {
    std::cerr << "Can't compute circle area: wrong radius" << std::endl;
    std::cout<<"Circle's area: ";
    return 0;
  }
}

rectangle_t Circle::getFrameRect() const {
  if (confirm != 0) {
    return{ pos, 2 * radius, 2 * radius };
  } else {
    std::cerr << "Error! Can not get frame: wrong radius"<< std::endl;
    return {{0.0, 0.0}, 0.0, 0.0};
  }
}
