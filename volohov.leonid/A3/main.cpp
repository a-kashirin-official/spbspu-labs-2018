#include <iostream>
#include <memory>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace volohov;

int main()
{
  Rectangle rectangle({1.1, 2.2}, 3.3, 4.4);
  Circle circle({1.0, 2.0}, 3.0);
  std::shared_ptr <Shape> rectanglePtr = std::make_shared <Rectangle> (rectangle);
  std::cout << "FrameRect parametrs:" << std::endl;
  std::cout << "Width:" << rectangle.getFrameRect().width << "Height:" << rectangle.getFrameRect().height << std::endl;
  std::cout << "Center:" << rectangle.getFrameRect().pos.x << ", " << rectangle.getFrameRect().pos.y << std::endl;

  std::shared_ptr <Shape> circlePtr = std::make_shared <Circle> (circle);
  std::cout << "Circle radius = " << circle.getFrameRect().width/2 << std::endl;
  std::cout << "Center:" << circle.getFrameRect().pos.x << ", " << circle.getFrameRect().pos.y << std::endl;

  std::cout << "Create composite shape" << std::endl;
  CompositeShape shapes(rectanglePtr);
  std::cout << "FrameRect parametrs:" << std::endl;
  std::cout << "Width:" << shapes.getFrameRect().width << "Height:" << shapes.getFrameRect().height << std::endl;
  std::cout << "Center:" << shapes.getFrameRect().pos.x << ", " << shapes.getFrameRect().pos.y << std::endl;

  std::cout << "Amount of shapes = " << shapes.getCount() << std::endl;
  std::cout << "Add circle" << std::endl;
  shapes.addShape(circlePtr);
  std::cout << "FrameRect parametrs:" << std::endl;
  std::cout << "Width:" << shapes.getFrameRect().width << "Height:" << shapes.getFrameRect().height << std::endl;
  std::cout << "Center:" << shapes.getFrameRect().pos.x << ", " << shapes.getFrameRect().pos.y << std::endl;

  std::cout << "Amount of shapes = " << shapes.getCount() << std::endl;
  shapes.scale(2);
  std::cout << "Composite shape after scaling on 2:" << std::endl;
  std::cout << "FrameRect parametrs:" << std::endl;
  std::cout << "Width:" << shapes.getFrameRect().width << "Height:" << shapes.getFrameRect().height << std::endl;
  std::cout << "Center:" << shapes.getFrameRect().pos.x << ", " << shapes.getFrameRect().pos.y << std::endl;

  std::cout << "Amount of shapes = " << shapes.getCount() << std::endl;
  std::cout << "Rectangle  after scaling composite shape:" << std::endl;
  std::cout << "FrameRect parametrs:" << std::endl;
  std::cout << "Width:" << rectangle.getFrameRect().width << "Height:" << rectangle.getFrameRect().height << std::endl;
  std::cout << "Center:" << rectangle.getFrameRect().pos.x << ", " << rectangle.getFrameRect().pos.y << std::endl;

  std::cout << "Circle after scaling composite shape:" << std::endl;
  std::cout << "Circle radius = " << circle.getFrameRect().width/2<< std::endl;
  std::cout << "Center:" << circle.getFrameRect().pos.x << ", " << circle.getFrameRect().pos.y << std::endl;

  shapes.move({5.0, 5.0});
  std::cout << "Composite shape after moving to {5.0, 5.0}:" << std::endl;
  std::cout << "FrameRect parametrs:" << std::endl;
  std::cout << "Width:" << shapes.getFrameRect().width << "Height:" << shapes.getFrameRect().height << std::endl;
  std::cout << "Center:" << shapes.getFrameRect().pos.x << ", " << shapes.getFrameRect().pos.y << std::endl;

  std::cout << "Amount of shapes = " << shapes.getCount() << std::endl;
  std::cout << "Rectangle after after moving composite shape:" << std::endl;
  std::cout << "FrameRect parametrs:" << std::endl;
  std::cout << "Width:" << rectangle.getFrameRect().width << "Height:" << rectangle.getFrameRect().height << std::endl;
  std::cout << "Center:" << rectangle.getFrameRect().pos.x << ", " << rectangle.getFrameRect().pos.y << std::endl;


  std::cout << "Circle after  after after moving composite shape:" << std::endl;
  std::cout << "Circle radius = " << circle.getFrameRect().width/2<< std::endl;
  std::cout << "Center:" << circle.getFrameRect().pos.x << ", " << circle.getFrameRect().pos.y << std::endl;

  shapes.removeShape(1);
  std::cout << "Shapes' amount after removing circle:" << shapes.getCount() << std::endl;

  return 0;
}
