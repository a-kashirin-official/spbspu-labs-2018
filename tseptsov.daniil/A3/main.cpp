#include <iostream>
#include <string>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"

using namespace tseptsov;

void OutDataShape(const Shape &shape)
{
  shape.OutData();
}

int main()
{

  try {
    Rectangle rectangle(1.0, 20.0, {13.0, 13.0});
    std::cout << "RECTANGLE" << std::endl;
    OutDataShape(rectangle);
    Circle circle(30.0, {13.0, 28.0});
    std::cout << "CIRCLE" << std::endl;
    OutDataShape(circle);
    Triangle triangle({12.0, 13.0}, {50.0, 60.0}, {19.0, 18.0});
    std::cout << "TRIANGLE" << std::endl;
    OutDataShape(triangle);
    std::shared_ptr < tseptsov::Shape > rectanglePtr = std::make_shared < tseptsov::Rectangle >(rectangle);
    std::shared_ptr < tseptsov::Shape > circlePtr = std::make_shared < tseptsov::Circle >(circle);
    std::shared_ptr < tseptsov::Shape > trianglePtr = std::make_shared < tseptsov::Triangle >(triangle);
    CompositeShape compositeshape(rectanglePtr);
    compositeshape.add(circlePtr);
    compositeshape.add(trianglePtr);
    std::cout << "COMPOSITE SHAPE" << std::endl;
    OutDataShape(compositeshape);
    std::cout << "Scaling and moving by axes" << std::endl;
    compositeshape.move(5, 4);
    compositeshape.scale(3);
    OutDataShape(compositeshape);
    std::cout << "Removing rectangle" << std::endl;
    compositeshape.remove(1);
    OutDataShape(compositeshape);
  }
  catch (std::invalid_argument &error) {
    std::cerr << error.what() << std::endl;
    return 1;
  }

  return 0;
}

