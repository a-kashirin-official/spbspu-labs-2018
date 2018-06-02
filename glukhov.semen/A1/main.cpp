#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

int main()
{


  Circle cir({ 0,0 }, 4);
  Shape*ptr = &cir;
  ptr->printShapeInfo();
  std::cout << "Area is = " << ptr->getArea() << "\n";
  ptr->move({ 15, 13 });
  std::cout << "Moving to [15,13]: " << "\n";
  ptr->printShapeInfo();
  ptr->move(11, 22);
  std::cout << "Moving on dx=11, dy=22" << "\n";
  ptr->printShapeInfo();
  std::cout << "\n";
  
  Triangle tri{ { 0, 0 },{ 9, 5 },{ 20, 0 } };
  ptr = &tri;
  ptr->printShapeInfo();
  std::cout << "Area is = " << ptr->getArea() << "\n";
  ptr->move({ 12, 15 });
  std::cout << "Moving to [12,15]: " << "\n";
  ptr->printShapeInfo();
  ptr->move(1, 2);
  std::cout << "After moving on dx=1, dy=2" << "\n";
  ptr->printShapeInfo();
  std::cout << "\n";

  Rectangle rect({ 0,0 }, 5, 10);
  ptr = &rect;
  ptr->printShapeInfo();
  std::cout << "Area is = " << ptr->getArea() << "\n";
  ptr->move({ 2,2 });
  std::cout << "Moving to [2,2]: " << "\n";
  ptr->printShapeInfo();
  ptr->move(11, 11);
  std::cout << "Moving on dx=11, dy=11" << "\n";
  ptr->printShapeInfo();
  std::cout << "\n";

  return 0;
}

