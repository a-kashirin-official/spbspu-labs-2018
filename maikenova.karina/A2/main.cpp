#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

void testShape(maikenova::Shape & thisShape)
{
  std::cout << "Area before scaling = " << thisShape.getArea() << std::endl;
  thisShape.scale(0.5);
  std::cout << "Area after scaling = " << thisShape.getArea() << std::endl;
}

int main()
{
  maikenova::Rectangle myRectangle({50, 50}, 10, 30);
  maikenova::Circle myCircle({50, 50}, 20);

  std::cout << "For the rectangle: " << std::endl;
  testShape(myRectangle);

  std::cout << "***" << std::endl;
  std::cout << "For the circle: " <<  std::endl;
  testShape(myCircle);

  return 0;
}
