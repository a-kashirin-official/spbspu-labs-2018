#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

using namespace zasyadko;

void poliPrint(Shape & testShape)
{
  testShape.print();
  std::cout << "Move by (10,10)" << std::endl;
  testShape.move(10,10);
  testShape.print();
  std::cout << "Move to (100,100)" << std::endl;
  testShape.move({100,100});
  testShape.print();
  std::cout << "Changing scale to 2" << std::endl;
  testShape.scale(2);
  testShape.print();
}

int main()
{
  Rectangle rectangleTest ({50,50},20,20);
  std::cout << "*****************" << std::endl;
  std::cout << "TESTING RECTANGLE" << std::endl;
  poliPrint(rectangleTest);
  std::cout << "*****************" << std::endl;
  
  Circle circleTest ({50,50},20);
  std::cout << "TESTING CIRCLE" << std::endl;
  poliPrint(circleTest);
  std::cout << "*****************" << std::endl;
  
  return 0;
}
  
  
