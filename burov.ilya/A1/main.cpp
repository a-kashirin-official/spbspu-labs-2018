#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"



void printShapeInfo(const Shape & obj)
{
  rectangle_t temp_data = obj.getFrameRect();
  std::cout << "Area: " << obj.getArea() << std::endl;
  std::cout << "   Center:" << std::endl;
  std::cout << "   x = " << temp_data.pos.x << std::endl;
  std::cout << "   y = " << temp_data.pos.y << std::endl;
  std::cout << "   height = " << temp_data.height << std::endl;
  std::cout << "   width = " << temp_data.width << std::endl;

}
int main()
{
  Circle circ{{20.0, 25.0}, 10.0};
  Rectangle rect{{{50.0, 50.0}, 20.0, 20.0}};
  std::cout << "CIRCLE in start position" << std::endl;
  printShapeInfo(circ);
  std::cout << "CIRCLE after moving" << std::endl;
  circ.move(44.0, 60.0);
  printShapeInfo(circ);


  std::cout << "RECTANGLE in start position" << std::endl;
  printShapeInfo(rect);
  std::cout << "RECTANGLE after moving" << std::endl;
  rect.move(35.0, 35.0);
  printShapeInfo(rect);
  return 0;

}
