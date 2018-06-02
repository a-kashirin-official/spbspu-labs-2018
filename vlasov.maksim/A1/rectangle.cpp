#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle(double _width, double _height, point_t _pos) :
  Shape(_pos),
  width(_width),
  height(_height)
{
  if ((width>=0.0) and (height>=0.0)) {
    std::cout << "rectangle constructed" << std::endl;
  } else {
    std::cerr << "Inaccessible area and frame: wrong dimensions" << std::endl;
    confirm = false;
  };
};

rectangle_t Rectangle::getFrameRect() const {
  if (confirm) {
    return {pos, width, height};
  } else {
    std::cerr << "Error! Can not get frame: wrong dimensions"<< std::endl;
    return {{0.0, 0.0}, 0.0, 0.0};
  }
}

double Rectangle::getArea() const {
  if (confirm) {
    std::cout <<"Rectangle's area ";
    return width*height;
  } else {
    std::cerr << "Can't compute rectangle area: wrong dimensions" << std::endl;
    std::cout<<"Rectangle's area: ";
    return 0;
  }
}
