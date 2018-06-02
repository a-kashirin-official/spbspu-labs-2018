#include <iostream>
#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

void printFrameRect(const  Shape &shape, const char *name)
{
  rectangle_t framerect = shape.getFrameRect();
  std::cout << "FrameRect " << name << std::endl;
  std::cout << " height " << framerect.height;
  std::cout << " width " << framerect.width;
  std::cout << " point.x " << framerect.pos.x;
  std::cout << " point.y " << framerect.pos.y << std::endl;
}

void printArea(const  Shape &shape, const char *name)
{
  std::cout << "Area " << name << " ";
  std::cout << shape.getArea() << std::endl;
}

int main()
{
  point_t center{ 1,3};

  Rectangle rectang(center, 5, 3);
  Circle circle(center, 2);
  printArea(rectang, "rectangle");
  printArea(circle, "circle");

  point_t point{ 0,0 };

  circle.move(point);
  rectang.move(4, 4);

  printFrameRect(rectang, "rectangle");
  printFrameRect(circle, "circle");

  return 0;
  
}
