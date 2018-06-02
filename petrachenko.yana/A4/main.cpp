#include <cmath>
#include <iostream>
#include "circle.hpp"
#include "matrix.hpp"
#include "rectangle.hpp"

using namespace petrachenko;

int main()
{
  point_t position = {10.0, 15.0};
  Rectangle *rectangle = new Rectangle(5.0, 10.3, position);
  rectangle->print();
  rectangle->rotate(90);
  rectangle->print();
  position = {10.0, 10.0};
  Circle *circle = new Circle(7.0, position);
  circle->print();
  circle->rotate(90);
  circle->print();
  try
  {
    Matrix mtrx(rectangle);
    mtrx.addShape(circle);
    mtrx.print();
  }
  catch (std::invalid_argument &ex)
  {
    std::cerr << ex.what() << std::endl;
    return 1;
  }
  catch (...) {
    std::cerr << "Error" << std::endl;
    return 2;
  }
  return 0;
}

