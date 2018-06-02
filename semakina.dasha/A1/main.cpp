#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  Rectangle rect({0, 0}, 50, 10);
  Shape *ptr = &rect;
  ptr -> output();
  std::cout << "Width of frame= " << ptr -> getFrameRect().width << std::endl;
  std::cout << "Height of frame = " << ptr -> getFrameRect().height << std::endl;
  std::cout << "Area of rectangle = " << ptr -> getArea() << std::endl;
  ptr -> move({60, 60});
  std::cout << "Move to {60, 60}" << std::endl;
  ptr -> output();
  ptr -> move(30, 20);
  std::cout << "Move on {30, 20}" << std::endl;
  ptr -> output();
  
  Circle circ({0, 0}, 50);
  ptr = &circ;
  ptr -> output();
  std::cout << "Width of frame= " << ptr -> getFrameRect().width << std::endl;
  std::cout << "Height of frame = " << ptr -> getFrameRect().height << std::endl;
  std::cout << "Area of circle = " << ptr -> getArea() << std::endl;
  ptr -> move({60, 60});
  std::cout << "Move to {60,60}" << std::endl;
  ptr -> output();
  ptr -> move(30, 20);
  std::cout << "Move on {30,20}" << std::endl;
  ptr -> output();
  return 0;
}
