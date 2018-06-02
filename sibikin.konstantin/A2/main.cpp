#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

void action(sibikin::Shape & currentObj)
{
  std::cout << "old area is " << currentObj.getArea() << std::endl;
  currentObj.scale(3.0);
  std::cout << "new area is " << currentObj.getArea() << std::endl;

  currentObj.move(3.3, 3.3);
  std::cout << "now pos is " << currentObj.getFrameRect().pos.x << "," << currentObj.getFrameRect().pos.y << std::endl;

  currentObj.move({3.3, 3.3});
  std::cout << "now pos is " << currentObj.getFrameRect().pos.x << "," << currentObj.getFrameRect().pos.y << std::endl;
}

int main()
{
  sibikin::Rectangle exRec({5,5}, 2, 2);
  sibikin::Circle exCircle({5,5}, 3);

  action(exRec);
  action(exCircle);
  return 0;
}

