#include <iostream>
#include <cmath>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace revtova;

int main()
{
  revtova::Rectangle rect({0.0,0.0}, 30.3, 10.2);
  revtova::CompositeShape CompShp (&rect);
  std::cout << rect.getArea() << std::endl;
  std::cout << CompShp.getArea() << std::endl;
  CompShp.scale(2);
  std::cout << "*2 = " << CompShp.getArea() << std::endl;

  std::cout << " " << std::endl;
  revtova::Circle circ1({0.0,0.0}, 30.5);
  CompShp.addShape(&circ1);
  std::cout << circ1.getArea() + rect.getArea() << std::endl;
  std::cout << CompShp.getArea() << std::endl;

  std::cout << " " << std::endl;
  revtova::Circle circ2({3.7, 1.2}, 14.7);
  CompShp.addShape(&circ2);
  std::cout << circ1.getArea() + circ2.getArea() + rect.getArea() << std::endl;
  std::cout << CompShp.getArea() << std::endl;

  std::cout << " " << std::endl;
  CompShp.remove(1);
  std::cout << rect.getArea() + circ2.getArea() << std::endl;
  std::cout << CompShp.getArea() << std::endl;

  return 0;
}
