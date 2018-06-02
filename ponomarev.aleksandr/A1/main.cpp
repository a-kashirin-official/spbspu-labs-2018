#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"

void testObj(Shape &thisObj)
{
  std::cout << "Area frame rectangle: " << thisObj.getArea() << std::endl;
  thisObj.getFrameRect();
  thisObj.move({3.2, 4.1});
  std::cout << "Move to (3.2, 4.1)\n";
  thisObj.move(4, 2);
  std::cout << "Move on (4, 2)\n";
  std::cout << "is now x = " << thisObj.getFrameRect().pos.x
  << ", y = " << thisObj.getFrameRect().pos.y << std::endl << std::endl;
}

int main()
{
  Rectangle objRectangle({0,0}, 6, 4);
  Circle objCircle({0,0}, 5);

  std::cout << "Rectangle:\n";
  testObj(objRectangle);

  std::cout << "Circle:\n";
  testObj(objCircle);

  return 0;
}
