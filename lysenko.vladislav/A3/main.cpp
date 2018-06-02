#include <iostream>
#include <stdexcept>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace lysenko;

void PrintParametrs(const Shape & object)
{
  std::cout << "Width of frame: " << object.getFrameRect().width << std::endl;
  std::cout << "Height of frame: " << object.getFrameRect().height << std::endl;
  std::cout << "Area of frame: " << object.getArea() << std::endl;
  std::cout << "Center: " << object.getFrameRect().pos.x << ", " << object.getFrameRect().pos.y << std::endl;;
}

int main()
{
  Rectangle rectangle( {0.0, 0.0}, 30.0, 10.0 );
  Circle circle( {0.0, 0.0}, 12.0);
  std::shared_ptr<Shape> rectangleptr = std::make_shared<Rectangle>(rectangle);
  std::shared_ptr<Shape> circleptr = std::make_shared<Circle>(circle);
  CompositeShape compositeshape(rectangleptr);
  PrintParametrs(compositeshape);
  compositeshape.addShape(circleptr);
  PrintParametrs(compositeshape);
  compositeshape.scale(2);
  PrintParametrs(compositeshape);
  return 0;
}
