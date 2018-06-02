#include <iostream>

#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

void printShapeInfo(const Shape & shape)
{
  std::cout << "Shape Info: " << "Area = " << shape.getArea() << ", ";
  std::cout << "Width = " << shape.getFrameRect().width << ", ";
  std::cout << "Height = " << shape.getFrameRect().height << "."  << std::endl;
}

void printShapeCoordinates(const Shape & shape)
{
  std::cout << "Center = {" << shape.getFrameRect().pos.x << "; ";
  std::cout << shape.getFrameRect().pos.y << "}"  << std::endl;
}

void moveShape(Shape & shape, const double x, const double y)
{
  shape.move(x + 1, y - 2);
  shape.move({ x - 5, y + 5 });
}

void testShape(Shape & shape)
{
  printShapeCoordinates(shape);
  moveShape(shape, 30, 45);
  std::cout << "Moved shape: ";
  printShapeCoordinates(shape);
}

int main() {
  Shape * shape = 0;
  try
  {
    Rectangle rectangle = Rectangle ({ -5.0, 10.0 }, 15.0, 10.0);
    Circle circle = Circle ({ 7.0, 0.0 }, 5.0);
    Triangle triangle = Triangle ({ 0.0, 0.0 }, { 3.0, 4.0 }, { 6.0, 0.0 });

    shape = & rectangle; // в.а.
    std::cout << "Rectangle" << std::endl;
    printShapeInfo(* shape);
    testShape(* shape); // разыменование

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
