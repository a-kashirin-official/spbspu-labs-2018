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
  std::cout << " pos.x " << framerect.pos.x;
  std::cout << " pos.y " << framerect.pos.y << std::endl;
}

void printArea(const  Shape &shape, const char *name)
{
  std::cout << "Area " << name << " ";
  std::cout << shape.getArea() << std::endl;
}

int main()
{
  point_t cent {4,6};

  Rectangle rect(cent, 5, 8);
  Circle circ(cent, 3);

  printArea(rect, "rectangle");
  printArea(circ, "circle");

  point_t point{ 2,2 };

  circ.move(point);
  rect.move(4, 4);

  printFrameRect(rect, "rectangle");
  printFrameRect(circ, "circle");

  circ.move(3, 3);
  rect.move(3, 3);

  std::cout << "Position has changed" << std::endl;

  printFrameRect(rect, "rectangle");
  printFrameRect(circ, "circle");

  return 0;
}

