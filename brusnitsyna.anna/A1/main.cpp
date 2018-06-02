#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

void testShape(Shape & myShape)
{
  std::cout << "Area: " << myShape.getArea() << std::endl;
  std::cout << "Frame: width = " << myShape.getFrameRect().width;
  std::cout << " height = " << myShape.getFrameRect().height << std::endl;

  myShape.move(1.1, 2);
  std::cout << "Pos: " << myShape.getFrameRect().pos.x << ", " << myShape.getFrameRect().pos.y << std::endl;
  myShape.move({2.2, 1});
  std::cout << "Pos: " << myShape.getFrameRect().pos.x << ", " << myShape.getFrameRect().pos.y << std::endl;
}

int main()
{
  Rectangle myRectangle({10, 5, {5, 1}});
  Circle myCircle({2, 1}, 5);

  testShape(myRectangle);
  testShape(myCircle);
  return 0;
}
