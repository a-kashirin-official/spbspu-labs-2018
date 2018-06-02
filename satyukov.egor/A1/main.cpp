#include <iostream>

#include "circle.hpp"
#include "rectangle.hpp"

void printCoordinates(const Shape & shape)
{
  const point_t testPoint = shape.getCoordinates();
  std::cout << "Center:" << std::endl;
  std::cout << "(" << testPoint.x << " ; " << testPoint.y << ")" << std::endl;
}

void printFrameRect(const Shape & shape)
{
  const rectangle_t testFrameRect = shape.getFrameRect();
  std::cout << "Get frame rectangle:" << std::endl;
  std::cout << "Center:" << std::endl;
  std::cout << "(" << testFrameRect.pos.x << " ; " << testFrameRect.pos.y << ")" << std::endl;
  std::cout << "Width, height:" << std::endl;
  std::cout << testFrameRect.width << ", " << testFrameRect.height << std::endl;
}

int main()
{
  Circle testCircle ({ 0.0, 0.0 }, 10.0);

  std::cout << "Default circle parametrs:" << std::endl;
  printCoordinates(testCircle);
  std::cout << "Radius:" << std::endl;
  std::cout << testCircle.getRadius() << std::endl;

  std::cout << "Get area:" << std::endl;
  std::cout << testCircle.getArea() << std::endl;

  std::cout << "Move to point (10.0 ; 5.0):" << std::endl;
  testCircle.move({ 10.0, 5.0 });
  printCoordinates(testCircle);

  printFrameRect(testCircle);

  std::cout << "Move to point (center_.x + 5.0 ; center_.y + 10.0):" << std::endl;
  testCircle.move(5.0, 10.0);
  printCoordinates(testCircle);

  Rectangle testRectangle ({ 0.0, 0.0 }, 10.0, 20.0);

  std::cout << "Default rectangle parametrs:" << std::endl;
  printCoordinates(testRectangle);
  std::cout << "Width, height:" << std::endl;
  std::cout << testRectangle.getWidth() << ", " << testRectangle.getHeight() << std::endl;

  std::cout << "Get area:" << std::endl;
  std::cout << testRectangle.getArea() << std::endl;

  std::cout << "Move to point (5.0 ; 10.0):" << std::endl;
  testRectangle.move({ 5.0, 10.0 });
  printCoordinates(testRectangle);

  printFrameRect(testRectangle);

  std::cout << "Move to point (center_.x + 20.0 ; center_.y + 15.0):" << std::endl;
  testRectangle.move(20.0, 15.0);
  printCoordinates(testRectangle);

  return 0;
}
