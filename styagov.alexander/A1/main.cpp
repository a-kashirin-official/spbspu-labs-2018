#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

#define NO_ERRORS 0
#define ERROR_INVALID_ARGUMENT 1
#define ERROR_BAD_ALLOCATION 2

void printShapeInfo(const Shape & shape)
{
  std::cout << "Shape information: Area = " << shape.getArea();
  std::cout << "; Width = " << shape.getFrameRect().width;
  std::cout << "; Height = " << shape.getFrameRect().height;
  std::cout << "."  << std::endl;
}

void printShapeCoordinates(const Shape & shape)
{
  std::cout << "Center: (" << shape.getPos().x;
  std::cout << "; " << shape.getPos().y;
  std::cout << "); Frame Rectangle center: (" << shape.getFrameRect().pos.x;
  std::cout << "; " << shape.getFrameRect().pos.y;
  std::cout << ")"  << std::endl;
}

void moveShape(Shape & shape, const double x, const double y)
{
  shape.move({ x, y });
  shape.move(x + 10.0, y - 10.0);
}

void testShape(Shape & shape)
{
  printShapeCoordinates(shape);

  moveShape (shape, 30.0, 45.0);

  std::cout << "After moving" << std::endl;
  printShapeCoordinates(shape);
}

int main() {
  Shape * shapePtr = 0;

  try
  {
    Rectangle rectangle = Rectangle({ -5.0, 10.0 }, 15.0, 10.0);
    Circle circle = Circle({ 7.0, 0.0 }, 5.0);
    Triangle triangle = Triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 });

    shapePtr = & rectangle;
    std::cout << "=== Testing Rectangle ===" << std::endl;
    printShapeInfo(* shapePtr);
    testShape(* shapePtr);

    shapePtr = & circle;
    std::cout << std::endl << "=== Testing Circle ===" << std::endl;
    printShapeInfo(* shapePtr);
    testShape(* shapePtr);

    shapePtr = & triangle;
    std::cout << std::endl << "=== Testing Triangle ===" << std::endl;
    printShapeInfo(* shapePtr);
    testShape(* shapePtr);
  }
  catch(const std::invalid_argument & exception)
  {
    std::cerr << exception.what() << std::endl;

    return ERROR_INVALID_ARGUMENT;
  }
  catch(const std::bad_alloc & exception)
  {
    std::cerr << exception.what() << std::endl;

    return ERROR_BAD_ALLOCATION;
  }

  return NO_ERRORS;
}
