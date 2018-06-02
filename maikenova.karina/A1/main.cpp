#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

void testShape(Shape & thisShape)
{
  std::cout << "Area of the rectangle: " << thisShape.getArea() << std::endl;
  thisShape.getFrameRect();
  thisShape.move({100, 100});
  std::cout << "New position is (100, 100)." << std::endl;
  thisShape.move(200, 200);
  std::cout << "Shifted by 200 in x-axes and by 200 in y-axes." << std::endl;
}
int main()
{
  Rectangle myRectangle({50, 50}, 10, 30);
  Circle myCircle({50, 50}, 20);

  std::cout << "Details of the rectangle: " << std::endl;
  testShape(myRectangle);

  std::cout << "***" << std::endl;
  std::cout << "Details of the circle: " <<  std::endl;
  testShape(myCircle);

  return 0;
}
