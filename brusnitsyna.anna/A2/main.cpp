#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

void testShape(brusnitsyna::Shape & myShape)
{
  std::cout << "Area: " << myShape.getArea() << std::endl;
  std::cout << "Frame: width = " << myShape.getFrameRect().width;
  std::cout << " height = " << myShape.getFrameRect().height << std::endl;
  myShape.scale(0.5);
  std::cout << "Area: " << myShape.getArea() << std::endl;
  std::cout << "Frame: width = " << myShape.getFrameRect().width;
  std::cout << " height = " << myShape.getFrameRect().height << std::endl;

  myShape.move(1.1, 2);
  std::cout << "Pos: " << myShape.getFrameRect().pos.x << ", " << myShape.getFrameRect().pos.y << std::endl;
  myShape.move({2.2, 1});
  std::cout << "Pos: " << myShape.getFrameRect().pos.x << ", " << myShape.getFrameRect().pos.y << std::endl;
  std::cout << std::endl;
}

int main()
{
  try {
    brusnitsyna::Rectangle myRectangle({10, 5, {5, 1}});
    brusnitsyna::Circle myCircle({2, 1}, 5);

    testShape(myRectangle);
    testShape(myCircle);
  } catch (std::invalid_argument & error) {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}
