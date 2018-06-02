#include <memory>
#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "shape.hpp"
using namespace reznik;

void Information(const CompositeShape & data)
{
  std::cout << "Area: " << data.getArea() << std::endl;
  std::cout << "Frame for object:" << std::endl;
  std::cout << "Center of frame: " << data.getFrameRect().pos.x << ", " << data.getFrameRect().pos.y << std::endl;
  std::cout << "Width of frame: " << data.getFrameRect().width << std::endl;
  std::cout << "Height of frame: " << data.getFrameRect().height << std::endl;
  std::cout << std::endl;
}

int main()
{
  std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle(6, 6, { 0,0 }));
  std::shared_ptr<Shape> circ = std::make_shared<Circle>(Circle(3, { 0,0 }));

  CompositeShape composite;
  composite.addShape(rect);
  composite.addShape(circ);
  Information(composite);
  composite.move(4, 5);
  Information(composite);
  composite.move({ 5,6 });
  Information(composite);
  composite.scale(2);
  Information(composite);
  return 0;
}
