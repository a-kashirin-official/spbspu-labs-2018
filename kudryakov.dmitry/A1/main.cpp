#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

void printShapePosition(const Shape &shape)
{
  std::cout << "Center is in the point ";
  std::cout << shape.getFrameRect().pos.x << ", "<< shape.getFrameRect().pos.y << std::endl;
}

void shapeDemonstration(Shape &shape, const char figureName[])
{
  std::cout << figureName << " demonstration: " << std::endl;
  std::cout << figureName << "'s frame width is " << shape.getFrameRect().width << std::endl;
  std::cout << figureName << "'s  frame height is " <<shape.getFrameRect().height << std::endl;
  std::cout << figureName << "'s area is " << shape.getArea() << std::endl;
  printShapePosition(shape);
  shape.move({5,5});
  std::cout << figureName << "'s center was moved to point" << std::endl;
  printShapePosition(shape);
  shape.move(5,0);
  std::cout << figureName << "'s center was moved by values" << std::endl;
  printShapePosition(shape);
  std::cout << std::endl;
}

int main()
{
  Rectangle rectangle({10,10}, 20, 30);
  shapeDemonstration(rectangle, "Rectangle");
  
  Circle circle({50,50}, 10);
  shapeDemonstration(circle, "Circle");
  
  return 0;
}
