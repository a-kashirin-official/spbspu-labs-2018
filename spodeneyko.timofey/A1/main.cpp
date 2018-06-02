#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  try
  {
    Rectangle rect({24.0, 48.0, {128.0, 256.0}});
    Shape * shapePtr = &rect;
    std::cout << "Rectangle:" << std::endl;
    std::cout << "Area = " << shapePtr -> getArea() << std::endl;
    rectangle_t shapeFrameRect = shapePtr -> getFrameRect();
    std::cout << "Coords: (" << shapeFrameRect.pos.x << ";" << shapeFrameRect.pos.y << ")" << std::endl;
    std::cout << "Width = " << shapeFrameRect.width << " Height = " << shapeFrameRect.height << std::endl;
    std::cout << std::endl;
    std::cout << "Move Rectangle to (123, 123):" << std::endl;
    shapePtr -> move({123.0, 123.0});
    shapeFrameRect = shapePtr -> getFrameRect();
    std::cout << "Coords: (" << shapeFrameRect.pos.x << ";" << shapeFrameRect.pos.y << ")" << std::endl;
    std::cout << "Width = " << shapeFrameRect.width << " Height = " << shapeFrameRect.height << std::endl;
    std::cout << std::endl;

    Circle circle(5.0, {10.0, 10.0});
    shapePtr = &circle;
    std::cout << "Circle:" << std::endl;
    std::cout << "Area of Circle = " << shapePtr -> getArea() << std::endl;
    shapeFrameRect = shapePtr -> getFrameRect();
    std::cout << "Coords: (" << shapeFrameRect.pos.x << ";" << shapeFrameRect.pos.y << ")" << std::endl;
    std::cout << "Width = " << shapeFrameRect.width << " Height = " << shapeFrameRect.height << std::endl;
    std::cout << std::endl;
    std::cout << "Move Circle (dx = 5.0, dy = -5.0):" << std::endl;
    shapePtr -> move(5.0, -5.0);
    shapeFrameRect = shapePtr -> getFrameRect();
    std::cout << "Coords: (" << shapeFrameRect.pos.x << ";" << shapeFrameRect.pos.y << ")" << std::endl;
    std::cout << "Width = " << shapeFrameRect.width << " Height = " << shapeFrameRect.height << std::endl;
  }
  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}
