#include <iostream>

#include "circle.hpp"
#include "rectangle.hpp"

void printFrameRect(const satyukov::Shape & shape)
{
  const satyukov::rectangle_t testFrameRect = shape.getFrameRect();
  std::cout << "Get frame rectangle:" << std::endl;
  std::cout << "Width, height:" << std::endl;
  std::cout << testFrameRect.width << ", " << testFrameRect.height << std::endl << std::endl;
}

int main()
{
  satyukov::Circle testCircle ({ 0.0, 0.0 }, 10.0);

  std::cout << "Сirlce before scaling:" << std::endl;
  std::cout << "Radius:" << std::endl;
  std::cout << testCircle.getRadius() << std::endl;
  std::cout << "Area:" << std::endl;
  std::cout << testCircle.getArea() << std::endl;
  printFrameRect(testCircle);
  testCircle.scale(5);
  std::cout << "Сirlce after scaling (coefficient = 5):" << std::endl;
  std::cout << "Radius:" << std::endl;
  std::cout << testCircle.getRadius() << std::endl;
  std::cout << "Area:" << std::endl;
  std::cout << testCircle.getArea() << std::endl;
  printFrameRect(testCircle);

  satyukov::Rectangle testRectangle ({ 0.0, 0.0 }, 10.0, 20.0);

  std::cout << "Rectangle before scaling:" << std::endl;
  std::cout << "Width, height:" << std::endl;
  std::cout << testRectangle.getWidth() << ", " << testRectangle.getHeight() << std::endl;
  std::cout << "Area:" << std::endl;
  std::cout << testRectangle.getArea() << std::endl;
  printFrameRect(testRectangle);
  testRectangle.scale(7.5);
  std::cout << "Rectangle after scaling (coefficient = 7.5):" << std::endl;
  std::cout << "Width, height:" << std::endl;
  std::cout << testRectangle.getWidth() << ", " << testRectangle.getHeight() << std::endl;
  std::cout << "Area:" << std::endl;
  std::cout << testRectangle.getArea() << std::endl;
  printFrameRect(testRectangle);

  return 0;
}
