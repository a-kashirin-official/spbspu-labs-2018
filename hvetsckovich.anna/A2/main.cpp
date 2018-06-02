#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

using namespace hvetsckovich;

void printShapeInfo(const Shape & shape)
{
  std::cout << "Shape Info: " << "Area = " << shape.getArea() << ", ";
  std::cout << "Width = " << shape.getFrameRect().width << ", ";
  std::cout << "Height = " << shape.getFrameRect().height << "."  << std::endl;
}

void printShapeCoordinates(const Shape & shape)
{
  std::cout << "Center (" << shape.getPos().x << "; ";
  std::cout << shape.getPos().y << ")"  << std::endl;
}

void moveShape(Shape & shape, const double x, const double y)
{
  shape.move({ x, y });
}

void scaleShape(Shape & shape, const double ratio)
{
  shape.scale(ratio);
}

void testShape(Shape & shape)
{
  printShapeCoordinates(shape);
  moveShape (shape, 20.0, 10.0);
  std::cout << "Moved shape: ";
  printShapeInfo(shape);
  printShapeCoordinates(shape);

  scaleShape(shape, 2.0);
  std::cout << "Scaled shape: ";
  printShapeInfo(shape);
  printShapeCoordinates(shape);
}

int main() {
  Shape * shape = nullptr;
  try
  {
    Rectangle rectangle = Rectangle ({ -5.0, 10.0 }, 15.0, 10.0 );
    Circle circle = Circle ({ 7.0, 0.0 }, 5.0);
    Triangle triangle = Triangle ({ 0.0, 0.0 }, { 3.0, 6.0 }, { 6.0, 0.0 });

    shape = & rectangle;
    std::cout << "Rectangle" << std::endl;
    printShapeInfo(* shape);
    testShape(* shape);

    shape = & circle;
    std::cout << std::endl << "Circle" << std::endl;
    printShapeInfo(* shape);
    testShape(* shape);

    shape = & triangle;
    std::cout << std::endl << "Triangle" << std::endl;
    printShapeInfo(* shape);
    testShape(* shape);
  }
  catch(const std::bad_alloc & exception)
  {
    std::cerr << exception.what() << std::endl;
    return 1;
  }
  catch(const std::invalid_argument & exception)
  {
    std::cout << exception.what() << std::endl;
    return 2;
  }

  return 0;
}
