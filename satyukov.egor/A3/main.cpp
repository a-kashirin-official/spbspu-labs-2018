#include <iostream>
#include <memory>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

void printCoordinates(const satyukov::Shape & shape)
{
  const satyukov::point_t testPoint = shape.getCoordinates();
  std::cout << "Center:" << std::endl;
  std::cout << "(" << testPoint.x << " ; " << testPoint.y << ")" << std::endl;
}

void printCoordinates(const std::shared_ptr < satyukov:: Shape > shape)
{
  const satyukov::point_t testPoint = shape->getCoordinates();
  std::cout << "(" << testPoint.x << " ; " << testPoint.y << ")" << std::endl;
}

void printInfo(const satyukov::Shape & shape)
{
  std::cout << "Area:" << std::endl;
  std::cout << shape.getArea() << std::endl;

  const satyukov::rectangle_t testFrameRect = shape.getFrameRect();
  std::cout << "Get frame rectangle:" << std::endl;
  std::cout << "Width, height:" << std::endl;
  std::cout << testFrameRect.width << ", " << testFrameRect.height << std::endl << std::endl;
}

int main()
{
  satyukov::Circle testCircle ({ 100.0, 0.0 }, 10.0);

  std::cout << "Сirlce before scaling:" << std::endl;
  std::cout << "Radius:" << std::endl;
  std::cout << testCircle.getRadius() << std::endl;
  printInfo(testCircle);
  testCircle.scale(5);
  std::cout << "Сirlce after scaling (coefficient = 5):" << std::endl;
  std::cout << "Radius:" << std::endl;
  std::cout << testCircle.getRadius() << std::endl;
  printInfo(testCircle);

  satyukov::Rectangle testRectangle ({ 0.0, 0.0 }, 10.0, 20.0);

  std::cout << "Rectangle before scaling:" << std::endl;
  std::cout << "Width, height:" << std::endl;
  std::cout << testRectangle.getWidth() << ", " << testRectangle.getHeight() << std::endl;
  printInfo(testRectangle);
  testRectangle.scale(2);
  std::cout << "Rectangle after scaling (coefficient = 2):" << std::endl;
  std::cout << "Width, height:" << std::endl;
  std::cout << testRectangle.getWidth() << ", " << testRectangle.getHeight() << std::endl;
  printInfo(testRectangle);

  std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
  std::shared_ptr < satyukov::Shape > rectanglePtr = std::make_shared < satyukov::Rectangle > (testRectangle);
  satyukov::CompositeShape testCompositeShape(circlePtr);

  std::cout << "Composite Shape = Circle:" << std::endl;
  printCoordinates(testCompositeShape);
  printInfo(testCompositeShape);
  testCompositeShape.addShape(rectanglePtr);
  std::cout << "Composite Shape = Circle + Rectangle:" << std::endl;
  printCoordinates(testCompositeShape);
  std::cout << "Center of Circle:" << std::endl;
  printCoordinates(testCompositeShape.getShape(0));
  std::cout << "Center of Rectangle:" << std::endl;
  printCoordinates(testCompositeShape.getShape(1));
  printInfo(testCompositeShape);
  testCompositeShape.scale(2);
  std::cout << "Composite Shape after scaling (coefficient = 2):" << std::endl;
  printCoordinates(testCompositeShape);
  std::cout << "Center of Circle:" << std::endl;
  printCoordinates(testCompositeShape.getShape(0));
  std::cout << "Center of Rectangle:" << std::endl;
  printCoordinates(testCompositeShape.getShape(1));
  printInfo(testCompositeShape);
  testCompositeShape.removeShape(0);
  std::cout << "Composite Shape = Rectangle:" << std::endl;
  printCoordinates(testCompositeShape);
  printInfo(testCompositeShape);
  testCompositeShape.clear();
  std::cout << "Composite Shape is empty:" << std::endl;
  printCoordinates(testCompositeShape);
  printInfo(testCompositeShape);

  return 0;
}
