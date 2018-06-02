#include <iostream>
#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "shape.hpp"

#include <memory>

using namespace zasyadko;

void infoPrint(const Shape & testShape)
{
  const rectangle_t frame = testShape.getFrameRect();
  std::cout << "Center is " << frame.pos.x << ", " << frame.pos.y << std::endl;
  std::cout << "Width is " << frame.width << std::endl;
  std::cout << "Height is " << frame.height << std::endl;
  std::cout << "Area is " << testShape.getArea() << std::endl;
}
int main()
{
  Rectangle testRect({30.0,30.0},10.0,10.0);
  Circle testCircle({40.0,40.0},10.0);
  std::shared_ptr <Shape> rectptr = std::make_shared <Rectangle>(testRect);
  std::shared_ptr <Shape> circptr = std::make_shared <Circle>(testCircle);
  CompositeShape compShape(rectptr);
  compShape.addShape(circptr);
  
  std::cout << "Composite Shape" << std::endl;
  infoPrint(compShape);
  compShape.scale(2);
  std::cout << "Scale factor 2" << std::endl;
  infoPrint(compShape);
  compShape.deleteShape(2);
  std::cout << "Deleting circle" << std::endl;
  infoPrint(compShape);
  compShape.deleteAll();
  std::cout << "Deleting composite shape" << std::endl;
  infoPrint(compShape);
  return 0;
}
  
