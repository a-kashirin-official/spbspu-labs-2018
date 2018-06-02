#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"

using namespace ponomarev;

void testObj(Shape &thisObj)
{
  std::cout << "Area frame rectangle: " << thisObj.getArea() << std::endl;
  thisObj.getFrameRect();
  thisObj.move({3.2, 4.1});
  std::cout << "Move to (3.2, 4.1)\n";
  thisObj.move(4.0, 2.0);
  std::cout << "Move on (4.0, 2.0)\n";
  std::cout << "is now x = " << thisObj.getFrameRect().pos.x
  << ", y = " << thisObj.getFrameRect().pos.y << std::endl;
  thisObj.scale(3.0);
  std::cout << "Area frame rectangle after scaling = "
  << thisObj.getArea() << std::endl << std::endl;
}

int main()
{
  Rectangle objRectangle({0,0}, 6.0, 4.0);
  Circle objCircle({0,0}, 5.0);

  std::cout << "Rectangle:\n";
  testObj(objRectangle);

  std::cout << "Circle:\n";
  testObj(objCircle);

  return 0;
}
