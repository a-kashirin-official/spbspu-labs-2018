#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  point_t point = {30, 130};

  Rectangle r({30, 70, point});
  Shape *rectangle = & r;
  std::cout << "Area of rectangle " << rectangle -> getArea() << std::endl;
  rectangle -> getFrameRect();
  rectangle -> move(70, -30);
  std::cout << "After moving" << std::endl;
  std::cout << "Area of rectangle " << rectangle -> getArea() << std::endl;
  rectangle -> getFrameRect();

  Circle c({200, 130}, 25);
  Shape *circle = & c;
  std::cout << "Area of circle " << circle -> getArea() << std::endl;
  circle -> getFrameRect();
  circle -> move({10, 10});
  std::cout << "After moving" <<std::endl;
  std::cout << "Area of circle " << circle -> getArea() << std::endl;
  circle -> getFrameRect();
  return 0;
}
