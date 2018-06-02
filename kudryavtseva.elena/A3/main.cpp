#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

int main()
{
  kudryavtseva::point_t t = {8.0,4.0}, coeff = {2.0,1.0};
  double coefficient = 3.0;
  kudryavtseva::Rectangle rect1(t, 3.0, 1.0);
  kudryavtseva::Circle circ1(t, 3.0);
  kudryavtseva::Rectangle rect2({6.0,8.0},6.0,8.0);
  kudryavtseva::Circle circ2 ({2.0, 3.0}, 8.0);

  kudryavtseva::CompositeShape comp;
  std::cout << "         Number of figures = " << comp.getSize() << std::endl;
  comp.add(&rect1);
  comp.add(&circ1);
  comp.add(&rect2);
  comp.add(&circ2);
  std::cout << "         Number of figures = " << comp.getSize() << std::endl;
  comp.printf();

  comp.removeShape(2);
  std::cout << "         Number of figures = " << comp.getSize() << std::endl;

  std::cout << "         After axial movement:" << std::endl;
  comp.move(3.0,4.0);
  comp.printf();
  std::cout << "         After moving to point:" << std::endl;
  comp.move(coeff);
  comp.printf();
  std::cout << "         After scaling " << coefficient << " times:" << std::endl;
  comp.scale(coefficient);
  comp.printf();

  return 0;
}
