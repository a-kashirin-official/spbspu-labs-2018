#include <iostream>

#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  Rectangle rect({20.0, 30.0, {100.0, 50.0}});
  Circle circle({50.0, 50.0}, 10.0);

  Shape * pointer = &rect;

  std::cout << "Rectangle demo" << std::endl;
  std::cout << "Coordinates X = " << pointer -> getFrameRect().pos.x << "Y = "
            << pointer -> getFrameRect().pos.y << std::endl;
  std::cout << "Width = " << pointer -> getFrameRect().width << std::endl;
  std::cout << "Height = " << pointer -> getFrameRect().height << std::endl;
  std::cout << "Area = " << pointer -> getArea() << std::endl;
  std::cout << "Move for (dx = 50.0, dy = 100.0)" << std::endl;
  pointer ->move(50.0, 100.0);
  std::cout << "New coordinates:" <<std::endl;
  std::cout << "Coordinates X = " << pointer -> getFrameRect().pos.x << "Y = "
            << pointer -> getFrameRect().pos.y << std::endl;
  std::cout << std::endl;

  pointer = &circle;

  std::cout << "Circle demo" << std::endl;
  std::cout << "Coordinates X = " << pointer -> getFrameRect().pos.x << "Y = "
            << pointer -> getFrameRect().pos.y << std::endl;
  std::cout << "Height = " << pointer -> getFrameRect().height << std::endl;
  std::cout << "Width = " << pointer -> getFrameRect().width << std::endl;
  std::cout << "Area = " << pointer ->getArea() << std::endl;
  std::cout << "Move to point (100.0, 100.0)" << std::endl;
  pointer -> move({100.0, 100.0});
  std::cout << "New coordinates:" <<std::endl;
  std::cout << "Coordinates X = " << pointer -> getFrameRect().pos.x << "Y = "
            << pointer -> getFrameRect().pos.y << std::endl;
  std::cout << std::endl;

  return 0;
}

