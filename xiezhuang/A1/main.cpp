#include "circle.hpp"
#include "rectangle.hpp"
#include <iostream>

int main()
{
  Rectangle rectangle({0, 0}, 10, 30);
  std::cout << "Rectangle" << std::endl;
  rectangle.printInfo();
  std::cout << "Area = " << rectangle.getArea() << std::endl;

  Circle circle({0, 0}, 50);
  std::cout << "Circle" << std::endl;
  circle.printInfo();
  std::cout << "Area = " << circle.getArea() << std::endl;

  std::cout << "Frame rectangles" << std::endl;
  std::cout << "for rectangle" << " center (" << rectangle.getFrameRect().pos.x << ", " << rectangle.getFrameRect().pos.y
            << ") width = " << rectangle.getFrameRect().width << " height = " << rectangle.getFrameRect().height << std::endl;
  std::cout << "for circle" << " center (" << circle.getFrameRect().pos.x << ", " << circle.getFrameRect().pos.y
            << ") width = " << circle.getFrameRect().width << " height = " << circle.getFrameRect().height << std::endl;

  std::cout << "Move rectangle to {10, -2}" << std::endl;
  rectangle.move({10, -2});
  rectangle.printInfo();
  std::cout << "Area = " << rectangle.getArea() << std::endl;
  std::cout << "Frame rectangle of rectangle" << " center (" << rectangle.getFrameRect().pos.x << ", "
            << rectangle.getFrameRect().pos.y << ") width = " << rectangle.getFrameRect().width
            << " height = " << rectangle.getFrameRect().height << std::endl;

  std::cout << "Move circle on (-5, 8)" << std::endl;
  circle.move(-5, 8);
  circle.printInfo();
  std::cout << "Area = " << circle.getArea() << std::endl;
  std::cout << "Frame rectangle of  circle" << " center (" << circle.getFrameRect().pos.x << ", "
            << circle.getFrameRect().pos.y << ") width = " << circle.getFrameRect().width
            << " height = " << circle.getFrameRect().height << std::endl;

  return 0;
}
