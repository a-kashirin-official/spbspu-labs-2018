#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  Rectangle shape_1({0, 0}, 5, 10);
  Shape *rectangle = &shape_1;
  rectangle->printInfo();
  
  std::cout << "Area is = " << rectangle->getArea() << std::endl;
  
  std::cout << "Shape move to {3, 3}" << std::endl;
  rectangle->move({3, 3});
  rectangle->printInfo();
  
  std::cout << "Shape move on (10, 10)" << std::endl;
  rectangle->move(10, 10);
  rectangle->printInfo();
  std::cout << std::endl;

  Circle shape_2({0, 0}, 3);
  Shape *circle = &shape_2;
  circle->printInfo();

  std::cout << "Area is = " << circle->getArea() << std::endl;
  
  std::cout << "Shape move to {15, 15}" << std::endl;
  circle->move({15, 15});
  circle->printInfo();
  
  std::cout << "Shape move on (22, 30)" << std::endl;
  circle->move(22, 30);
  circle->printInfo();
  std::cout << std::endl;
  
  return 0;
}
