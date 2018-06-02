#include <iostream>
#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

int main()
{
  grigorev::Rectangle rectangle({1.0, 1.0}, 5.0, 6.0);
  grigorev::Circle circle({5.0, 5.0}, 3.0);
  std::shared_ptr< grigorev::Shape > rectanglePtr = std::make_shared< grigorev::Rectangle >(rectangle);
  std::shared_ptr< grigorev::Shape > circlePtr = std::make_shared< grigorev::Circle >(circle);

  grigorev::CompositeShape comp;
  std::cout << "Size of empty figure= " << comp.getSize() << std::endl;
  std::cout << std::endl;

  comp.addShape(rectanglePtr);
  std::cout << "Info about composite shape" << std::endl;
  std::cout << "Size of figure = " << comp.getSize() << std::endl;
  std::cout << "Coordinates of center: " << std::endl;
  std::cout << "(" << comp.getFrameRect().pos.x << ";" << comp.getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Area is " << comp.getArea() << std::endl;
  std::cout << "Parametrs of FrameRect" << std::endl;
  std::cout << "Width " << comp.getFrameRect().width << " Height " << comp.getFrameRect().height << std::endl;
  std::cout << std::endl;

  comp.addShape(circlePtr);
  std::cout << "Info about composite shape after adding another shape " << std::endl;
  std::cout << "Size of figure = " << comp.getSize() << std::endl;
  std::cout << "Coordinates of center: " << std::endl;
  std::cout << "(" << comp.getFrameRect().pos.x << ";" << comp.getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Area is " << comp.getArea() << std::endl;
  std::cout << "Parametrs of FrameRect" << std::endl;
  std::cout << "Width " << comp.getFrameRect().width << " Height " << comp.getFrameRect().height << std::endl;
  std::cout << std::endl;

  comp.removeShape(2);
  std::cout << "Info about composite shape after remove circle" << std::endl;
  std::cout << "Size of figure = " << comp.getSize() << std::endl;
  std::cout << "Coordinates of center: " << std::endl;
  std::cout << "(" << comp.getFrameRect().pos.x << ";" << comp.getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Area is " << comp.getArea() << std::endl;
  std::cout << "Parametrs of FrameRect" << std::endl;
  std::cout << "Width " << comp.getFrameRect().width << " Height " << comp.getFrameRect().height << std::endl;
  std::cout << std::endl;

  comp.addShape(circlePtr);
  comp.move({3.0, 3.0});
  std::cout << "Info about composite shape after moving to point" << std::endl;
  std::cout << "Coordinates of center: " << std::endl;
  std::cout << "(" << comp.getFrameRect().pos.x << ";" << comp.getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Area is " << comp.getArea() << std::endl;
  std::cout << "Parametrs of FrameRect" << std::endl;
  std::cout << "Width " << comp.getFrameRect().width << " Height " << comp.getFrameRect().height << std::endl;
  std::cout << std::endl;

  comp.move(4.0, 4.0);
  std::cout << "Info about composite shape after moving by dx, dy" << std::endl;
  std::cout << "Coordinates of center: " << std::endl;
  std::cout << "(" << comp.getFrameRect().pos.x << ";" << comp.getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Area is " << comp.getArea() << std::endl;
  std::cout << "Parametrs of FrameRect" << std::endl;
  std::cout << "Width " << comp.getFrameRect().width << " Height " << comp.getFrameRect().height << std::endl;
  std::cout << std::endl;

  comp.scale(2.0);
  std::cout << "Info about composite shape after scaling" << std::endl;
  std::cout << "Size of figure = " << comp.getSize() << std::endl;
  std::cout << "Coordinates of center: " << std::endl;
  std::cout << "(" << comp.getFrameRect().pos.x << ";" << comp.getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Area is " << comp.getArea() << std::endl;
  std::cout << "Parametrs of FrameRect" << std::endl;
  std::cout << "Width " << comp.getFrameRect().width << " Height " << comp.getFrameRect().height << std::endl;
  std::cout << std::endl;

  comp.deleteShapes();
  std::cout << "Info about composite shape after remove all figures" << std::endl;
  std::cout << "Size of figure = " << comp.getSize() << std::endl;

  return 0;
}
