#include <iostream>

#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

using namespace lobanova;

int main()
{
  point_t centre = {0, 0};
  Rectangle r1(centre, 2, 2);
  CompositeShape c;
  c.add(&r1);
  std::cout << c.getArea() << std::endl;
  Circle c1({2, 2}, 1);
  c.add(&c1);
  std::cout << c.getCentre().x << " " << c.getCentre().y << std::endl;
  c.scale(2);
  std::cout << c.getCentre().x << " " << c.getCentre().y << std::endl;
}
