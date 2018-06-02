#include <iostream>
#include "shape.hpp"


void Shape::move(const point_t &arrival)
{
  pos = arrival;
}

void Shape::move(const double difX, const double difY)
{
  pos.x += difX;
  pos.y += difY;
}

void Shape::showPosition() const {
  std::cout << "Figure's position (x, y): " << pos.x << " " << pos.y << std::endl;
}

Shape::Shape(const point_t &_pos):
  pos(_pos)
{
}
