#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"

void printInfo(const pichugina::Shape & object)
{
  std::cout << "Area: " << object.getArea() << std::endl;
  const pichugina::rectangle_t frame = object.getFrameRect();
  std::cout << "Frame for object:" << std::endl;
  std::cout << "Middle " << frame.pos.x << ", " << frame.pos.y << std::endl;
  std::cout << "Width " << frame.width << std::endl;
  std::cout << "Height " << frame.height << std::endl;
}

int main()
{
  pichugina::Circle circle{ { 3.31, 24.11 }, 10.41 };
  pichugina::Rectangle rectangle{ { 11.55, 2.24 }, 7.53, 6.81 };
  
  std::cout << "Circle:" << std::endl;
  printInfo(circle);
  circle.move( 4.24, 3.12 );
  printInfo(circle);
  std::cout << "Moving" << std::endl;
  circle.move( { 45.91, 43.41 } );
  printInfo(circle);
  std::cout << "Expansion" << std::endl;
  circle.scale(3.0);
  printInfo(circle);

  std::cout << "Rectangle:" << std::endl;
  printInfo(rectangle);
  rectangle.move( -5.61, 42.18 );
  printInfo(rectangle);
  std::cout << "Moving" << std::endl;
  rectangle.move( { 3.03, 1.17 } );
  printInfo(rectangle);
  std::cout << "Expansion" << std::endl;
  rectangle.scale(1.5);
  printInfo(rectangle);

  return 0;
}
