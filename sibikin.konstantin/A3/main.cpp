#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

void action(sibikin::Shape & currentObj)
{
  std::cout << "old area is " << currentObj.getArea() << std::endl;
  std::cout << "now pos is " << currentObj.getFrameRect().pos.x << ", " << currentObj.getFrameRect().pos.y << std::endl;
  currentObj.scale(0.5);
  std::cout << "new area is " << currentObj.getArea() << std::endl;
  std::cout << "now pos is " << currentObj.getFrameRect().pos.x << ", " << currentObj.getFrameRect().pos.y << std::endl;

  currentObj.move(3.3, 3.3);
  std::cout << "now pos is " << currentObj.getFrameRect().pos.x << ", " << currentObj.getFrameRect().pos.y << std::endl;

  currentObj.move({3.3, 3.3});
  std::cout << "now pos is " << currentObj.getFrameRect().pos.x << ", " << currentObj.getFrameRect().pos.y << std::endl;
}

int main()
{
  sibikin::Rectangle exRec({5.0, 5.0}, 2.0, 3.0);
  sibikin::Circle exCircle({3.0, 3.0}, 2.0);

  sibikin::CompositeShape exComp;
  exComp.addShape(&exRec);
  exComp.addShape(&exCircle);

  sibikin::CompositeShape test(&exRec);
  std::cout << exComp.getSize() << ' ' << exComp.getPos().x << ',' << exComp.getPos().y << std::endl;
  std::cout << test.getSize() << ' ' << test.getPos().x << ',' << test.getPos().y << std::endl;
  test = exComp;
  std::cout << exComp.getSize() << ' ' << exComp.getPos().x << ',' << exComp.getPos().y << std::endl;
  std::cout << test.getSize() << ' ' << test.getPos().x << ',' << test.getPos().y << std::endl;
  action(exComp);
  return 0;
}
