#include "circle.hpp"
#include "rectangle.hpp"

#include <iostream>

void printFrameRect(const  Shape &sh, const char *name);
void printArea(const  Shape &sh, const char *name);

int main()
{
  point_t centre{ 6, 4 };
  point_t newpos{ -1, 6 };

  Circle circle(centre, 18.2);
  printArea(circle, "Circle ");
  circle.move(newpos);
  printFrameRect(circle, "Circle ");
  circle.move(-3, 12);
  printFrameRect(circle, "Circle ");

  std::cout << std::endl;

  Rectangle rectangle(centre, 8, 11);
  printArea(rectangle, "Rectangle ");
  rectangle.move(newpos);
  printFrameRect(rectangle, "Rectangle ");
  rectangle.move(5, -6);
  printFrameRect(rectangle, "Rectangle ");

  return 0;
}

void printFrameRect(const Shape &sh, const char *name)
{
  rectangle_t framerect = sh.getFrameRect();
  std::cout << "FrameRect " << name << std::endl
            << "pos.x " << framerect.pos.x
            << " pos.y " << framerect.pos.y
            << " width " << framerect.width
            << " height " << framerect.height<< std::endl;
}

void printArea(const Shape &sh, const char *name)
{
  std::cout << "Area " << name <<" "
            << sh.getArea() << std::endl;
}
