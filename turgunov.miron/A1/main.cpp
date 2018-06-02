#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

int main()
{
  Rectangle rect({0, 0}, 15, 8);
  Shape *ptr = &rect;
  ptr->printShapeInfo();
  std::cout << "Area is = " << ptr->getArea() << "\n";
  std::cout << "Shape move to {6, 3}\n";
  ptr->move({6, 3});
  ptr->printShapeInfo();
  std::cout << "Shape move on (20, 10)\n";
  ptr->move(20, 10);
  ptr->printShapeInfo();
  std::cout << "\n";

  Circle cir({0, 0}, 3);
  ptr = &cir;
  ptr->printShapeInfo();
  std::cout << "Area is = " << ptr->getArea() << "\n";
  std::cout << "Shape move to {15, -10}\n";
  ptr->move({15, -10});
  ptr->printShapeInfo();
  std::cout << "Shape move on (2, 30)\n";
  ptr->move(2, 30);
  ptr->printShapeInfo();
  std::cout << "\n";

  Triangle tri({0, 0}, {10, 10},{20, 0});
  ptr = &tri;
  ptr->printShapeInfo();
  std::cout << "Area is = " << ptr->getArea() << "\n";
  std::cout << "Shape move to {10, 5}\n";
  ptr->move({10, 5});
  ptr->printShapeInfo();
  std::cout << "Shape move on (3, 3)\n";
  ptr->move(3, 3);
  ptr->printShapeInfo();
  std::cout << "\n";
  
  return 0;
}
