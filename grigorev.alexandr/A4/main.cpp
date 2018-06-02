#include <iostream>
#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

int main()
{
  grigorev::Rectangle rectangle({1.0, 1.0}, 5.0, 6.0);
  grigorev::Circle circle({5.0, 5.0}, 3.0);
  grigorev::CompositeShape comp;
  std::shared_ptr< grigorev::Shape > rectanglePtr = std::make_shared< grigorev::Rectangle >(rectangle);
  std::shared_ptr< grigorev::Shape > circlePtr = std::make_shared< grigorev::Circle >(circle);

  rectangle.rotate(90);
  std::cout << "Info about rectangle after rotate" << std::endl;
  std::cout << "Parametrs of FrameRect" << std::endl;
  std::cout << "Width " << rectangle.getFrameRect().width << " Height " << rectangle.getFrameRect().height << std::endl;
  std::cout << std::endl;
  rectangle.rotate(270);

  comp.addShape(rectanglePtr);
  comp.addShape(circlePtr);
  std::cout << "Info about composite shape" << std::endl;
  std::cout << "Parametrs of FrameRect" << std::endl;
  std::cout << "Width " << comp.getFrameRect().width << " Height " << comp.getFrameRect().height << std::endl;
  std::cout << std::endl;
  comp.rotate(90);
  std::cout << "Info about composite shape after rotate" << std::endl;
  std::cout << "Parametrs of FrameRect" << std::endl;
  std::cout << "Width " << comp.getFrameRect().width << " Height " << comp.getFrameRect().height << std::endl;
  std::cout << std::endl;

  grigorev::Rectangle rectangle1({3.0, 2.0}, 10.0, 10.0);
  grigorev::Rectangle rectangle2({1.0, 1.0}, 5.0, 6.0);
  grigorev::Circle circle1({-3.0, -4.0}, 3.0);
  grigorev::Circle circle2({5.0, 5.0}, 5.0);

  std::shared_ptr< grigorev::Shape > rectanglePtr1 = std::make_shared< grigorev::Rectangle >(rectangle1);
  std::shared_ptr< grigorev::Shape > rectanglePtr2 = std::make_shared< grigorev::Rectangle >(rectangle2);
  std::shared_ptr< grigorev::Shape > circlePtr1 = std::make_shared< grigorev::Circle >(circle1);
  std::shared_ptr< grigorev::Shape > circlePtr2 = std::make_shared< grigorev::Circle >(circle2);

  grigorev::Matrix matrix(rectanglePtr1);
  matrix.addShape(rectanglePtr2);
  matrix.addShape(circlePtr1);
  matrix.addShape(circlePtr2);

  return 0;
}
