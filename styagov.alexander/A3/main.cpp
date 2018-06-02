#include <iostream>
#include <memory>

#include "circle.hpp"
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

using namespace styagov;

void printShapeCoordinates(const styagov::Shape & shape)
{
  std::cout << "Center (";
  std::cout << shape.getPos().x << "; ";
  std::cout << shape.getPos().y << "), ";
  std::cout << "frame rectangle center (";
  std::cout << shape.getFrameRect().pos.x << "; ";
  std::cout << shape.getFrameRect().pos.y << ")";
  std::cout << std::endl;
}

void printShapeInfo(const styagov::Shape & shape)
{
  std::cout << "Area = " << shape.getArea() << "; ";
  std::cout << "Width = " << shape.getFrameRect().width << "; ";
  std::cout << "Height = " << shape.getFrameRect().height << ".";
  std::cout << std::endl;
  printShapeCoordinates(shape);
  std::cout << std::endl;
}

void moveShape(styagov::Shape & shape, const double x, const double y)
{
  shape.move({ x, y });
  std::cout << "Moving in (" << x << "; " << y << ")" << std::endl;
  printShapeInfo(shape);

  shape.move(x / 2.0, y / 2.0);
  std::cout << "Shifting by " << (x / 2.0) << " to right and by " << (y / 2.0) << " to top.";
  std::cout << std::endl;
  printShapeInfo(shape);
}

void scaleShape(styagov::Shape & shape, const double ratio)
{
  shape.scale(ratio);
  std::cout << "Scaling by " << ratio << "." << std::endl;
  printShapeInfo(shape);

  shape.scale(1.0 / ratio);
  std::cout << "Downscaling to default size." << std::endl;
  printShapeInfo(shape);
}

void testShape(styagov::Shape & shape)
{
  printShapeInfo(shape);
  moveShape(shape, 10.0, 20.0);
  scaleShape(shape, 4.0);
}

int main() {
  std::shared_ptr< styagov::Shape > shapePtr = nullptr;

  try
  {
    styagov::Circle circle = Circle({ 7.0, 0.0 }, 5.0);
    styagov::Rectangle rectangle = Rectangle({ -5.0, 10.0 }, 15.0, 10.0);
    styagov::Triangle triangle = Triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 });

    shapePtr = std::make_shared< styagov::Circle >(circle);
    std::cout << std::endl << "=== Testing Circle ===" << std::endl;
    testShape(* shapePtr);
    styagov::CompositeShape compositeShape(shapePtr);

    shapePtr = std::make_shared< styagov::Rectangle >(rectangle);
    compositeShape.add(shapePtr);
    std::cout << "=== Testing Rectangle ===" << std::endl;
    testShape(* shapePtr);

    shapePtr = std::make_shared< styagov::Triangle >(triangle);
    compositeShape.add(shapePtr);
    std::cout << std::endl << "=== Testing Triangle ===" << std::endl;
    testShape(* shapePtr);

    std::cout << "=== Testing Composite Shape ===" << std::endl;
    testShape(compositeShape);
    std::cout << "*** Removed Rectangle from Composite Shape ***" << std::endl;
    compositeShape.remove(1);
    testShape(compositeShape);
    std::cout << "*** Removing all remain shapes from Composite Shape ***" << std::endl;
    compositeShape.clearShapes();
    testShape(compositeShape);
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
