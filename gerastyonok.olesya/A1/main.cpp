#include <iostream>
#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

void testShape(Shape & shape)
{
  std::cout << "Area: " << shape.getArea() << std::endl;
  std::cout << "Frame: height = " << shape.getFrameRect().height << " width = " << shape.getFrameRect().width << std::endl;

  shape.move({ 7, 3 });
  std::cout << "Area: " << shape.getArea() << std::endl;
  shape.move(3, 7);
  std::cout << "Area: " << shape.getArea() << std::endl;
}

int main()
{
  Rectangle sRectangle({ 2 , 7 , { 0 , 0 } });
  Circle sCircle(5, {0, 0});
  Triangle sTriangle({1, 3} , {4 , 1} , {6 , 4});

  std::cout << "Rectangle: " << std::endl;
  testShape(sRectangle);
  std::cout << "Circle: " << std::endl;
  testShape(sCircle);
  std::cout << "Triangle: " << std::endl;
  testShape(sTriangle);
  return 0;
}
