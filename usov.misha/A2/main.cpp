#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include <cstdlib>
using namespace usov;
int main()
{
  Rectangle rect(32, 32, { 10,10 });
  Shape *ptr = &rect;
  ptr->print();
  std::cout << "Area of rectangle: " << ptr->getArea() << std::endl;
  ptr->move(3, 3);
  ptr->print();
  ptr->move({ 5,5 });
  ptr->print();
  ptr->scale(5);
  ptr->print();
  
  Circle circ(12, { 32,32 });
  ptr = &circ;
  ptr->print();
  std::cout << "Area of circle: " << ptr->getArea() << std::endl;
  ptr->move(3, 3);
  ptr->print();
  ptr->move({ 5,5 });
  ptr->print();
  ptr->scale(4);
  ptr->print();
  return 0;
}
