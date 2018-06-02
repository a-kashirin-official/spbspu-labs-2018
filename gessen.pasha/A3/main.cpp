#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include <iostream>
using namespace gessen;

int main()
{
  Rectangle *rect = new Rectangle({128.0, 256.0}, 14.0, 57.0);
  rect->printShapeName();
  CompositeShape composeShape(rect);
  std::cout << "After creating" << std::endl;
  composeShape.printShapeName();

  std::cout << std::endl;

  Circle *circ = new Circle ({59.0, 61.0}, 10.0);
  circ->printShapeName();
  composeShape.addShape(circ);
  std::cout << "After adding circle" << std::endl;
  composeShape.printShapeName();

  std::cout << std::endl;

  composeShape.removeShape(0);
  std::cout << "After removing rectangle" << std::endl;
  composeShape.printShapeName();

  std::cout << std::endl;

  composeShape.scale(2.0);
  std::cout << "After scaling" << std::endl;
  composeShape.printShapeName();

  std::cout << std::endl;

  composeShape.move({138.0, 127.0});
  std::cout << "After moving to point" << std::endl;
  composeShape.printShapeName();

  std::cout << std::endl;

  composeShape.move(138.0, 127.0);
  std::cout << "After moving on parametrs" << std::endl;
  composeShape.printShapeName();
}
