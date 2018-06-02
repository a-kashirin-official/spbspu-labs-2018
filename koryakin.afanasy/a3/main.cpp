#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

int main()
{
  using namespace koryakin;

  Rectangle rect({ 14.0, 19.0 }, 3.0, 5.0);
  std::cout << "rect.getArea: " <<rect.getArea() << std::endl;
  CompositeShape testComp(&rect);
  std::cout << "testComp.getArea  " <<testComp.getArea() << std::endl;
  
  Circle circ({ 40.0, 90.0 }, 20.0);
  testComp.addShape(&circ);
  std::cout << "circ.getArea() + rect.getArea() " << circ.getArea() + rect.getArea() << std::endl;
  std::cout << "testComp.getArea: " <<testComp.getArea() << std::endl;
  
  testComp.removeShape(0);
  std::cout << "circ.getArea: " <<circ.getArea() << std::endl;
  std::cout << "testComp.getArea() " <<testComp.getArea() << std::endl;
  
  testComp.clear();
  return 0;
} // koryakin 13534/6
