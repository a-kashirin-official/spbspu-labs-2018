#include <iostream>
#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "shape.hpp"
#include <memory>

using namespace vasilev;

void getLog(const Shape &testShape)
{
  const rectangle_t frame = testShape.getFrameRect();
  std::cout << "Center is " << frame.pos.x << ", " << frame.pos.y << std::endl;
  std::cout << "Width is " << frame.width << std::endl;
  std::cout << "Height is " << frame.height << std::endl;
  std::cout << "Area is " << testShape.getArea() << std::endl;
}
int main()
{
  Rectangle testRect(40, 20, {100, 100});
  Circle testCircle(20, {150, 150});
  std::shared_ptr <Shape> rectptr = std::make_shared <Rectangle>(testRect);
  std::shared_ptr <Shape> circptr = std::make_shared <Circle>(testCircle);
  CompositeShape Comp(rectptr);
  Comp.addShape(circptr);

  std::cout << "Composite Shape" << std::endl;
  Comp.getInfo();
  Comp.scale(2);
  std::cout << std::endl << "Scale factor 2" << std::endl;
  Comp.getInfo();
  Comp.deleteShape(2);
  std::cout << std::endl << "Deleting circle" << std::endl;
  Comp.getInfo();
  return 0;
}
