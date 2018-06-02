#include <iostream>
#include <stdexcept>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace semakina;

namespace semakina
{
  void printInfo(const Shape & shape)
  {
    std::cout << "Center: " << shape.getFrameRect().pos.x << ", " << shape.getFrameRect().pos.y << std::endl;
    std::cout << "Width of frame = " << shape.getFrameRect().width << std::endl;
    std::cout << "Height of frame = " << shape.getFrameRect().height << std::endl;
    std::cout << "Area of rectangle = " << shape.getArea() << std::endl;
  }
}

int main()
{
  try
  {
    Rectangle rect({0, 0}, 50, 10);
    Circle circ({0, 0}, 50);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);

    std::cout << "CompositeShape = Rectangle" << std::endl;
    printInfo(compositeshape);

    compositeshape.addShape(circPtr);
    std::cout << "CompositeShape = Rectangle and Circle" << std::endl;
    printInfo(compositeshape);

    std::cout << "Scale(2)" << std::endl;
    compositeshape.scale(2);
    printInfo(compositeshape);

    std::cout << "Move to {60, 60}" << std::endl;
    compositeshape.move({60, 60});
    printInfo(compositeshape);

    std::cout << "Move on {30, 20}" << std::endl;
    compositeshape.move(30, 20);
    printInfo(compositeshape);

    std::cout << "Delete Circle" << std::endl;
    compositeshape.deleteShape(1);
    printInfo(compositeshape);

    std::cout << "Clear CompositeShape" << std::endl;
    compositeshape.clear();
    printInfo(compositeshape);
  }
  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}
