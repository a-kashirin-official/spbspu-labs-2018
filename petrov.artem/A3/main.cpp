#include <iostream>
#include <memory>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

void printInfo(const petrov::Shape & object)
{
  std::cout << "Area: " << object.getArea() << std::endl;
  const petrov::rectangle_t frame = object.getFrameRect();
  std::cout << "Frame for object:" << std::endl;
  std::cout << "\tMiddle of frame: " << frame.pos.x << ", " << frame.pos.y << std::endl;
  std::cout << "\tWidth of frame: " << frame.width << std::endl;
  std::cout << "\tHeight of frame: " << frame.height << std::endl;
}

int main()
{
  petrov::Circle circle{ { 5.32, 27.63 }, 10.01 };
  petrov::Rectangle rectangle{ { 25.04, 6.12 }, 7.13, 4.82 };
  std::shared_ptr< petrov::Shape > circlePtr = std::make_shared< petrov::Circle >(circle);
  std::shared_ptr< petrov::Shape > rectanglePtr = std::make_shared< petrov::Rectangle >(rectangle);
  petrov::CompositeShape compositeShape(circlePtr);


  std::cout << "Circle:" << std::endl;
  printInfo(circle);
  circle.move( 2.45, 6.16 );
  printInfo(circle);
  circle.move( { 52.90, 73.21 } );
  printInfo(circle);
  circle.scale(3.0);
  printInfo(circle);
  std::cout << std::endl;

  std::cout << "Rectangle:" << std::endl;
  printInfo(rectangle);
  rectangle.move( -5.23, 19.08 );
  printInfo(rectangle);
  rectangle.move( { 3.03, 21.17 } );
  printInfo(rectangle);
  rectangle.scale(1.5);
  printInfo(rectangle);
  std::cout << std::endl;

  std::cout << "Composite shape:" << std::endl;
  printInfo(compositeShape);
  compositeShape.addShape(rectanglePtr);
  printInfo(compositeShape);
  compositeShape.scale(2.0);
  printInfo(compositeShape);
  compositeShape.removeShape(1);
  printInfo(compositeShape);
  compositeShape.deleteShapes();
  printInfo(compositeShape);
  return 0;
}
