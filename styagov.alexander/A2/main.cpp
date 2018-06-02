#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

using namespace styagov;

void printShapeCoordinates(const Shape & shape)
{
  std::cout << "Center (";
  std::cout << shape.getPos().x << "; ";
  std::cout << shape.getPos().y << "), ";
  std::cout << "frame rectangle center (";
  std::cout << shape.getFrameRect().pos.x << "; ";
  std::cout << shape.getFrameRect().pos.y << ")";
  std::cout << std::endl;
}

void printShapeInfo(const Shape & shape)
{
  std::cout << "Area = " << shape.getArea() << "; ";
  std::cout << "Width = " << shape.getFrameRect().width << "; ";
  std::cout << "Height = " << shape.getFrameRect().height << ".";
  std::cout << std::endl;
  printShapeCoordinates(shape);
  std::cout << std::endl;
}

void moveShape(Shape & shape, const double x, const double y)
{
  shape.move({ x, y });
  std::cout << "Moving in (" << x << "; " << y << ")" << std::endl;
  printShapeInfo(shape);

  shape.move(x / 2.0, y / 2.0);
  std::cout << "Shifting by " << (x / 2.0) << " to right and by " << (y / 2.0) << " to top.";
  std::cout << std::endl;
  printShapeInfo(shape);
}

void scaleShape(Shape & shape, const double ratio)
{
  shape.scale(ratio);
  std::cout << "Scaling by " << ratio << "." << std::endl;
  printShapeInfo(shape);

  shape.scale(1.0 / ratio);
  std::cout << "Downscaling to default size." << std::endl;
  printShapeInfo(shape);
}

void testShape(Shape & shape)
{
  printShapeInfo(shape);
  moveShape(shape, 10, 20);
  scaleShape(shape, 4.0);
}

int main() {
  Shape * shapePtr = nullptr;

  try
  {
    Rectangle rectangle = Rectangle({ -5.0, 10.0 }, 15.0, 10.0);
    Circle circle = Circle({ 7.0, 0.0 }, 5.0);
    Triangle triangle = Triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 });

    shapePtr = & rectangle;
    std::cout << "=== Testing Rectangle ===" << std::endl;
    testShape(* shapePtr);

    shapePtr = & circle;
    std::cout << std::endl << "=== Testing Circle ===" << std::endl;
    testShape(* shapePtr);

    shapePtr = & triangle;
    std::cout << std::endl << "=== Testing Triangle ===" << std::endl;
    testShape(* shapePtr);
  }
  catch(const std::invalid_argument & exception)
  {
    std::cerr << exception.what() << std::endl;

    return 1;
  }
  catch(const std::bad_alloc & exception)
  {
    std::cerr << exception.what() << std::endl;

    return 2;
  }

  return 0;
}
