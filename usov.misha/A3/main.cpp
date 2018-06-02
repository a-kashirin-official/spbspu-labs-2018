#include <memory>
#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "shape.hpp"
using namespace usov;

void Information(const Shape & data)
{
  std::cout << "Area: " << data.getArea() << std::endl;
  const rectangle_t frame = data.getFrameRect();
  std::cout << "Frame for object:" << std::endl;
  std::cout << "Center of frame: " << frame.pos.x << ", " << frame.pos.y << std::endl;
  std::cout << "Width of frame: " << frame.width << std::endl;
  std::cout << "Height of frame: " << frame.height << std::endl;
  std::cout << std::endl;
}

int main()
{
  std::shared_ptr<Shape> rect = std::make_shared<Rectangle>(Rectangle(4, 4, { 0,0 }));
  std::shared_ptr<Shape> circ = std::make_shared<Circle>(Circle(2, { 0,0 }));
  CompositeShape composite(circ);
  composite.addShape(rect);
  Information(composite);
  composite.move(4, 4);
  Information(composite);
  composite.move({ 5,5 });
  Information(composite);
  composite.scale(2);
  Information(composite);
  composite.print();
  return 0;
}
