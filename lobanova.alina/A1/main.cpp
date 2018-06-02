#include <iostream>
#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"


int main()
{
  Circle c = {{5, 5}, 3};
  std::cout << "Area of circle: " << c.getArea() << std::endl;
  rectangle_t i = c.getFrameRect();
  Rectangle rect = {i.pos, i.width, i.height};
  std::cout << "Area of circle's frame rectangle: " << rect.getArea() << std::endl;
  std::cout << "Rectangle centre is: x = " << rect.getFrameRect().pos.x << ", y = " << rect.getFrameRect().pos.y
            << std::endl;
  std::cout << "Rectangle is moving to point (2, 9)" << std::endl;
  rect.move({2, 9});
  std::cout << "New rectangle centre is: x = " << rect.getFrameRect().pos.x << ", y = " << rect.getFrameRect().pos.y
            << std::endl;
  std::cout << "Rectangle is moving to vector (1, 0)" << std::endl;
  rect.move(1, 0);
  std::cout << "New rectangle centre is: x = " << rect.getFrameRect().pos.x << ", y = " << rect.getFrameRect().pos.y
            << std::endl;

  std::cout << "Same areas using class shape:" << std::endl;
  Shape *ptr = &rect;
  std::cout << ptr->getArea() << std::endl;
  ptr = &c;
  std::cout << ptr->getArea() << std::endl;

}
