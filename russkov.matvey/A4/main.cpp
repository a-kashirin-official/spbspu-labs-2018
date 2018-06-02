#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

int main()
{
  russkov::point_t p = {128.0, 256.0};
  std::shared_ptr<russkov::Shape> rectPtr (new russkov::Rectangle(p,24.0, 48.0));
  std::shared_ptr<russkov::Shape> circlePtr(new russkov::Circle(p,4.0));
  russkov::CompositeShape comp_shape(rectPtr);
  comp_shape.addShape(circlePtr);
  std::cout<< comp_shape.getArea() << "\n";
  comp_shape.rotate(90.0);
  std::cout<< comp_shape.getArea() << "\n";
  comp_shape.move(34.0, 43.0);
  comp_shape.rotate(20.0);
  std::cout<< comp_shape.getArea() << "\n";
  comp_shape.deleteShape(1);

  russkov::Matrix matr(rectPtr);
  matr.addShape(circlePtr);
  return 0;
}
