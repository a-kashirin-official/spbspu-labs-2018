#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

int main()
{
  try
  {
  kudryavtseva::point_t coeff = {2.0,1.0};
  double coefficient = 3.0;
  kudryavtseva::Rectangle rect1({8.0,4.0}, 3.0, 1.0);
  kudryavtseva::Circle circ1({8.0,4.0}, 3.0);
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

  kudryavtseva::Matrix matrix1(&rect1);
  matrix1.add(&circ2);
  matrix1.add(&comp);
  matrix1.add(&circ1);
  matrix1.add(&rect2);
  matrix1.print();
  }
  catch(...)
  {
    std::cout<<"1";
  }
  return 0;
}
