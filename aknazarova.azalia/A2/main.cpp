#include <iostream>

#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

using namespace aknazarova;
void printFrameRect(const  Shape &shape, const char *name)
{
  rectangle_t framerect = shape.getFrameRect();
  std::cout << "FrameRect " << name << std::endl;
  std::cout << " Height " << framerect.height;
  std::cout << " Width " << framerect.width;
  std::cout << " pos(x)= " << framerect.pos.x;
  std::cout << " pos(y)= " << framerect.pos.y << std::endl;
}

void printArea(const  Shape &shape, const char *name)
{
  std::cout << "Area " << name << " ";
  std::cout << shape.getArea() << std::endl;
}

int main()
{
  point_t cent {8.3,10.2};

  Rectangle rect(cent, 3.6, 2);
  Circle circ(cent, 4.2);

  printArea(rect, "Rectangle");
  printArea(circ, "Circle");

  point_t point{ 5.3, 6.6 };

  circ.move(point);
  rect.move(3.4, 5);

  printFrameRect(rect, "Rectangle");
  printFrameRect(circ, "Circle");

  circ.move(-2.8, 2);
  circ.scale(3);
  rect.move(5.8, 6);
  rect.scale(3);

  std::cout << "Position has changed, the figure is multipied by the coefficient 3." << std::endl;

  printFrameRect(rect, "Rectangle");
  printFrameRect(circ, "Circle");

  circ.move(10.54, 9);
  circ.scale(5);
  rect.move(-2.8, -2.6);
  rect.scale(5);

  std::cout << "Position has changed, the figure is multipied by the coefficient 5." << std::endl;

  printFrameRect(rect, "Rectangle");
  printFrameRect(circ, "Circle");

  return 0;
}
