#include "rectangle.hpp"
#include "circle.hpp"
#include <iostream>

int main()
{
  Rectangle rect(10,2,{10,15});
  Shape *ptr = &rect;
  Circle circ(3,{5,5});
  Shape *pcr = &circ;
  std::cout << "Area of circle: " << pcr->getArea() << std::endl;
  std::cout << "Area of rectangle: " << ptr->getArea() << std::endl << std::endl;
  ptr->move({34,50});
  pcr->move({10,15});
  std::cout << "Frame of rectangle" << std::endl;
  std::cout << "Height: " << ptr->getFrameRect().height << std::endl;
  std::cout << "Width: " << ptr->getFrameRect().width << std::endl << std::endl;
  std::cout << "Frame of circle" << std::endl;
  std::cout << "Height: " << pcr->getFrameRect().height << std::endl;
  std::cout << "Width: " << pcr->getFrameRect().width << std::endl;
  ptr->move(5,3);
  pcr->move(15,13);
  return 0;
}
