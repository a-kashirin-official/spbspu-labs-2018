#include <iostream>
#include "circle.hpp"
#include "composite-shape.hpp"
#include "rectangle.hpp"

using namespace petrachenko;

int main()
{
  point_t position = {10.0, 15.0};
  Rectangle *rectangle = new Rectangle(5.0, 10.3, position);
  rectangle->print();
  position = {1.0, 1.0};
  Circle *circle = new Circle(7.0, position);
  circle->print();
  CompositeShape CompositeShape(rectangle);
  CompositeShape.addShape(circle);
  CompositeShape.print();
  return 0;
}

