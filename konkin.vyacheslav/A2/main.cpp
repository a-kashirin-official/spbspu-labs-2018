#include <iostream>

#include "circle.hpp"
#include "rectangle.hpp"

using namespace konkin;

int main()
{
  try
  {
    Rectangle rect({20.0, 30.0, {100.0, 50.0}});
    Circle circle({50.0, 50.0}, 10.0);

    Shape * pointer = &rect;

    std::cout << "Rectangle demo" << std::endl;
    std::cout << "Coordinates X = " << pointer -> getFrameRect().pos.x << " Y = "
              << pointer -> getFrameRect().pos.y << std::endl;
    std::cout << "Width = " << pointer -> getFrameRect().width << std::endl;
    std::cout << "Height = " << pointer -> getFrameRect().height << std::endl;
    std::cout << "Area = " << pointer -> getArea() << std::endl;
    std::cout << "Scaling of rectangle. Coefficient = 10" << std::endl;
    pointer -> scale(10);
    std::cout << "New width = " << pointer -> getFrameRect().width << std::endl;
    std::cout << "New height = " << pointer -> getFrameRect().height << std::endl;
    std::cout << "New area = " << pointer -> getArea() << std::endl;

    std::cout << "Move for (dx = 50.0, dy = 100.0)" << std::endl;
    pointer ->move(50.0, 100.0);
    std::cout << "New coordinates:" <<std::endl;
    std::cout << "Coordinates X = " << pointer -> getFrameRect().pos.x << " Y = "
              << pointer -> getFrameRect().pos.y << std::endl;
    std::cout << std::endl;

    pointer = &circle;

    std::cout << "Circle demo" << std::endl;
    std::cout << "Coordinates X = " << pointer -> getFrameRect().pos.x << " Y = "
              << pointer -> getFrameRect().pos.y << std::endl;
    std::cout << "Height = " << pointer -> getFrameRect().height << std::endl;
    std::cout << "Width = " << pointer -> getFrameRect().width << std::endl;
    std::cout << "Area = " << pointer ->getArea() << std::endl;
    std::cout << "Scaling of circle. Coefficient = 5" << std::endl;
    pointer -> scale(5);
    std::cout << "New width = " << pointer -> getFrameRect().width << std::endl;
    std::cout << "New height = " << pointer -> getFrameRect().height << std::endl;
    std::cout << "New area = " << pointer -> getArea() << std::endl;

    std::cout << "Move to point (100.0, 100.0)" << std::endl;
    pointer -> move({100.0, 100.0});
    std::cout << "New coordinates:" <<std::endl;
    std::cout << "Coordinates X = " << pointer -> getFrameRect().pos.x << " Y = "
              << pointer -> getFrameRect().pos.y << std::endl;
    std::cout << std::endl;
  }
  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
    return 0;
}
