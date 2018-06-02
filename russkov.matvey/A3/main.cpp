#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

int main()
{
  russkov::point_t p = {128.0, 256.0};
  std::shared_ptr<russkov::Shape> rectPtr (new russkov::Rectangle(p,24.0, 48.0));
  std::shared_ptr<russkov::Shape> circlePtr(new russkov::Circle(p,4.0));
  russkov::CompositeShape comp_shape(rectPtr);
  comp_shape.addShape(circlePtr);
  std::cout<< comp_shape.getArea() << "\n";
  comp_shape.move({11.0, 12.0});
  std::cout<< comp_shape.getArea() << "\n";
  comp_shape.move(34.0, 43.0);
  comp_shape.scale(20.0);
  std::cout<< comp_shape.getArea() << "\n";
  comp_shape.deleteShape(1);
  return 0;
}
