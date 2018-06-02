#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

void printFrameRect(const  Shape &shape1, const char *name)
{
  rectangle_t framerect = shape1.getFrameRect();
  std::cout << "FrameRect " << name << std::endl
    << "pos.x " << framerect.pos.x
    << " pos.y " << framerect.pos.y
    << " width " << framerect.width
    << " height " << framerect.height << std::endl;
}

void printArea(const  Shape &shape1, const char *name)
{
  std::cout << "Area " << name
    << shape1.getArea() << std::endl;
}

int main()
{
  point_t centre{ 2.2, 4.3 };
  point_t newpos{ -1.1, -1.9 };

  Circle Circle1(centre, 3.4);
  printArea(Circle1, "Circle ");
  Circle1.move(newpos);
  printFrameRect(Circle1, "Circle ");
  Circle1.move(-9.0, 5.6);
  printFrameRect(Circle1, "Circle ");

  std::cout << std::endl;

  Rectangle Rectangle1(centre, 4.7, 8.5);
  printArea(Rectangle1, "Rectangle ");
  Rectangle1.move(newpos);
  printFrameRect(Rectangle1, "Rectangle ");
  Rectangle1.move(5.0, -6.5);
  printFrameRect(Rectangle1, "Rectangle ");

  return 0;
}

