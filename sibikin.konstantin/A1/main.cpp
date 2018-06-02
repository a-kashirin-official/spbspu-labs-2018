#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

void action(Shape & currentObj)
{
  std::cout << "area is " << currentObj.getArea() << std::endl;
  std::cout << "w = " << currentObj.getFrameRect().width << ", h = " << currentObj.getFrameRect().height << std::endl;

  currentObj.move(3.3, 3.3);
  std::cout << "now pos is " << currentObj.getFrameRect().pos.x << "," << currentObj.getFrameRect().pos.y << std::endl;

  currentObj.move({3,3});
  std::cout << "now pos is " << currentObj.getFrameRect().pos.x << "," << currentObj.getFrameRect().pos.y << std::endl;
}

int main()
{
  Rectangle exRec({5,5}, 2, 4);
  Circle exCircle({5,5}, 3);

  action(exRec);
  action(exCircle);
  return 0;
}

