#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  Rectangle shape_1({0, 0}, 5, 3);
  Shape *rectangle = &shape_1;
  rectangle->printInfo();
  
  std::cout << "Area is = " << rectangle->getArea() << "\n";
  
  std::cout << "Shape move to {20, -8}\n";
  rectangle->move({20, -8});
  rectangle->printInfo();
  
  std::cout << "Shape move on (10, 0)\n";
  rectangle->move(10, 0);
  rectangle->printInfo();
  std::cout << "\n";

  Circle shape_2({0, 0}, 1);
  Shape *circle = &shape_2;
  circle->printInfo();

  std::cout << "Area is = " << circle->getArea() << "\n";
  
  std::cout << "Shape move to {3, 8}\n";
  circle->move({3, 8});
  circle->printInfo();
  
  std::cout << "Shape move on (2, -9)\n";
  circle->move(2, -9);
  circle->printInfo();
  std::cout << "\n";
  
  return 0;
}
