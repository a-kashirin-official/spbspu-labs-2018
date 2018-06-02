#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  Circle c({1,1}, 10);
  Shape *circle = &c;
  std::cout << "CIRCLE" << "\n";
  circle->printInfo();
  std::cout << "Area: " << circle->getArea() << "\n";
  std::cout << "Height of frame rectangle:" << circle->getFrameRect().height << "\n"
            << "Width of frame rectangle:" << circle->getFrameRect().width << "\n"
            << "Coordinates of frame rectangle: (" << circle->getFrameRect().pos.x
            << "," << circle->getFrameRect().pos.y << ") \n";
  std::cout << "Move to point (12, 3) \n";
  circle->move({12,3});
  circle->printInfo();
  std::cout << "Move on dx = 2, dy = 2 \n";
  circle->move(2, 2);
  circle->printInfo();

  std::cout << "\n";

  Rectangle r({0,0}, 20, 15);
  Shape *rectangle = &r;
  std::cout << "RECTANGLE \n";
  rectangle->printInfo();
  std::cout << "Area: " << rectangle->getArea() << "\n"
            << "Height of frame rectangle:" << rectangle->getFrameRect().height << "\n"
            << "Width of frame rectangle:" << rectangle->getFrameRect().width << "\n"
            << "Coordinates of frame rectangle: (" << rectangle->getFrameRect().pos.x
            << "," << rectangle->getFrameRect().pos.y << ") \n"
            << "Move to point (5, 5) \n";
  rectangle->move({5, 5});
  rectangle->printInfo();
  std::cout << "Move on dx = 1.5, dy = 1.5 \n";
  rectangle->move(1.5, 1.5);
  rectangle->printInfo();

  return 0;
}
