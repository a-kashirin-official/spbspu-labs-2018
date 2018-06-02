#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include <iostream>
#include <memory>

using namespace dumaev;

int main()
{
  Circle circle({1,1}, 9);
  std::cout << "CIRCLE" << "\n"
            << "Coordinates: (" << circle.getPos().x << "," << circle.getPos().y << ") \n"
            << "Area: " << circle.getArea() << "\n"
            << "Height of frame rectangle:" << circle.getFrameRect().height << "\n"
            << "Width of frame rectangle:" << circle.getFrameRect().width << "\n"
            << "Coordinates of frame rectangle: (" << circle.getFrameRect().pos.x
            << "," << circle.getFrameRect().pos.y << ") \n"
            << "Move to point (12, 3) \n";
  circle.move({12,3});
  std::cout << "Coordinates: (" << circle.getPos().x << "," << circle.getPos().y << ") \n"
            << "Move on dx = -5, dy = 2 \n";
  circle.move(-5, 2);
  std::cout << "Coordinates: (" << circle.getPos().x << "," << circle.getPos().y << ") \n"
            << "Scaling with coefficient = 3 \n";
  circle.scale(3);
  std::cout << "Height of frame rectangle:" << circle.getFrameRect().height << "\n"
            << "Width of frame rectangle:" << circle.getFrameRect().width << "\n"
            << "Area: " << circle.getArea() << "\n\n";

  Rectangle rectangle({0,0}, 20, 15);
  std::cout << "RECTANGLE \n"
            << "Coordinates: (" << rectangle.getPos().x << "," << rectangle.getPos().y << ") \n"
            << "Area: " << rectangle.getArea() << "\n"
            << "Height of frame rectangle:" << rectangle.getFrameRect().height << "\n"
            << "Width of frame rectangle:" << rectangle.getFrameRect().width << "\n"
            << "Coordinates of frame rectangle: (" << rectangle.getFrameRect().pos.x
            << "," << rectangle.getFrameRect().pos.y << ") \n"
            << "Move to point (5, 5) \n";
  rectangle.move({5, 5});
  std::cout << "Coordinates: (" << rectangle.getPos().x << "," << rectangle.getPos().y << ") \n"
            << "Move on dx = 1, dy = 1 \n";
  rectangle.move(1, 1);
  std::cout << "Coordinates: (" << rectangle.getPos().x << "," << rectangle.getPos().y << ") \n"
            << "Scaling with coefficient = 2 \n";
  rectangle.scale(2);
  std::cout << "Height of frame rectangle:" << rectangle.getFrameRect().height << "\n"
            << "Width of frame rectangle:" << rectangle.getFrameRect().width << "\n"
            << "Area: " << rectangle.getArea() << "\n\n";

  std::shared_ptr < Shape > circlePtr = std::make_shared < Circle > (circle);
  std::shared_ptr < Shape > rectanglePtr = std::make_shared < Rectangle > (rectangle);
  CompositeShape compositeShape(circlePtr);
  compositeShape.addShape(rectanglePtr);
  std::cout << "COMPOSITE SHAPE: rectangle and circle \n";
  std::cout << "Coordinates: (" << compositeShape.getPos().x << "," << compositeShape.getPos().y << ") \n";
  std::cout << "Area: " << compositeShape.getArea() << "\n"
            << "Height of frame rectangle:" << compositeShape.getFrameRect().height << "\n"
            << "Width of frame rectangle:" << compositeShape.getFrameRect().width << "\n"
            << "Coordinates of frame rectangle: (" << compositeShape.getFrameRect().pos.x
            << "," << compositeShape.getFrameRect().pos.y << ") \n"
            << "Move to point (9, 7) \n";
  compositeShape.move({9, 7});
  std::cout << "Coordinates: (" << compositeShape.getPos().x << "," << compositeShape.getPos().y << ") \n";
  std::cout << "Move on dx = 2, dy = 2 \n";
  compositeShape.move(2, 2);
  std::cout << "Coordinates: (" << compositeShape.getPos().x << "," << compositeShape.getPos().y << ") \n";
  std::cout << "Scaling with coefficient = 2 \n";
  compositeShape.scale(2);
  std::cout << "Height of frame rectangle:" << compositeShape.getFrameRect().height << "\n"
            << "Width of frame rectangle:" << compositeShape.getFrameRect().width << "\n";

  return 0;
}
