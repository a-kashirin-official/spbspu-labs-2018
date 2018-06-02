#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

void demonstration(Shape *ptr)
{
  ptr->showSize();
  ptr->showPos();
  std::cout << "The area of the figure is " << ptr->getArea() << std::endl;
  rectangle_t boundingRect(ptr->getFrameRect());
  std::cout << "The size of the bounding rectangle: ";
  std::cout << "Width = " << boundingRect.width << " Height = " << boundingRect.height << std::endl;
  ptr->move(25.0,25.0);
  std::cout << "The center of the figure was moved." << std::endl;
  ptr->showPos();
  ptr->move({50.0,50.0});
  std::cout << "The center of the figure was moved." << std::endl;
  ptr->showPos();
  std::cout << std::endl;
}

int main()
{
  Rectangle rectangle({5.0,5.0},30.0,50.0);
  std::cout << "Rectangle: " << std::endl;
  demonstration(&rectangle);
  Circle circle({ 10.0,10.0 }, 45.0);
  std::cout << "Circle: " << std::endl;
  demonstration(&circle);
  Triangle triangle({3.0,3.0}, {12.0,4.0}, {8.0,8.0});
  std::cout << "Triangle: " << std::endl;
  demonstration(&triangle);
  return 0;
}
