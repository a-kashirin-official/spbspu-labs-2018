#include <iostream>
#include <stdexcept>
#include "circle.hpp"
#include "rectangle.hpp"

using namespace semakina;

int main()
{
  try
  {
    Rectangle rect({0, 0}, 50, 10);
    Shape * ptr = & rect;
    std::cout << "Center: " << ptr -> getFrameRect().pos.x << ", " << ptr -> getFrameRect().pos.y << std::endl;
    std::cout << "Width of frame = " << ptr -> getFrameRect().width << std::endl;
    std::cout << "Height of frame = " << ptr -> getFrameRect().height << std::endl;
    std::cout << "Area of rectangle = " << ptr -> getArea() << std::endl;
    ptr -> move({60, 60});
    std::cout << "Move to {60, 60}" << std::endl;
    std::cout << "Center: " << ptr -> getFrameRect().pos.x << ", " << ptr -> getFrameRect().pos.y << std::endl;
    ptr -> move(30, 20);
    std::cout << "Move on {30, 20}" << std::endl;
    std::cout << "Center: " << ptr -> getFrameRect().pos.x << ", " << ptr -> getFrameRect().pos.y << std::endl;
    ptr -> scale(2);
    std::cout << "Width of frame = " << ptr -> getFrameRect().width << std::endl;
    std::cout << "Height of frame = " << ptr -> getFrameRect().height << std::endl;

    Circle circ({0, 0}, 50);
    ptr = & circ;
    std::cout << "Center: " << ptr -> getFrameRect().pos.x << ", " << ptr -> getFrameRect().pos.y << std::endl;
    std::cout << "Width of frame = " << ptr -> getFrameRect().width << std::endl;
    std::cout << "Height of frame = " << ptr -> getFrameRect().height << std::endl;
    std::cout << "Area of circle = " << ptr -> getArea() << std::endl;
    ptr -> move({60, 60});
    std::cout << "Move to {60, 60}" << std::endl;
    std::cout << "Center: " << ptr -> getFrameRect().pos.x << ", " << ptr -> getFrameRect().pos.y << std::endl;
    ptr -> move(30, 20);
    std::cout << "Move on {30, 20}" << std::endl;
    std::cout << "Center: " << ptr -> getFrameRect().pos.x << ", " << ptr -> getFrameRect().pos.y << std::endl;
    ptr -> scale(2);
    std::cout << "Width of frame = " << ptr -> getFrameRect().width << std::endl;
    std::cout << "Height of frame = " << ptr -> getFrameRect().height << std::endl;
  }
  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}
