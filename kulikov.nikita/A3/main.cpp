#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
using namespace kulikov;

int main (int, char *[])
{
  try
  {
    Rectangle rect({ {0.0,0.0}, 3.0, 5.0});
    Circle circ({{0.0, 0.0}, 3.0});
    std::shared_ptr <Shape> rectanglePtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circlePtr = std::make_shared <Circle> (circ);
    CompositeShape composite(rectanglePtr);
    composite.addShape(circlePtr);
    composite.scale(3.0);
    composite.move({30.0, 20.0});
    composite.deleteShape(1);
    composite.clear();
  }
  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  return 0;
}
