#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include <iostream>

void printInfo(const kahuanahil::Shape & shape)
{
  std::cout << "Width: " << shape.getFrameRect().width << std::endl;
  std::cout << "Height: " << shape.getFrameRect().height << std::endl;
  std::cout << "Center( " << shape.getFrameRect().pos.x << "; "<< shape.getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Area: " << shape.getArea() << std::endl;
  
 }

int main()
{
  kahuanahil::Rectangle rec({10.0, 20.0, {36.0, 48.0}});
  std::shared_ptr<kahuanahil::Shape> rect = std::make_shared<kahuanahil::Rectangle>(rec);
  kahuanahil::CompositeShape composite_shape(rect);
  std::cout << "Rectangle: " << std::endl;
  printInfo(rec);
  std::cout << "Composite shape with Rectangle: " << std::endl;
  printInfo(composite_shape);
  std::cout << "Shape was added(Circle)" << std::endl;
  kahuanahil::Circle cir(3.0, {5.0, 5.0});
  std::shared_ptr<kahuanahil::Shape> circ = std::make_shared<kahuanahil::Circle> (cir);
  composite_shape.addShape(circ);
  printInfo(composite_shape);
  std::cout << "Move to (10, 5) " << std::endl;
  composite_shape.move({10.0, 5.0});
  printInfo(composite_shape);
  std::cout << "Scale (2.0)" << std::endl;
  composite_shape.scale(2.0);
  printInfo(composite_shape);
  std::cout << "Delete Shape " << std::endl;
  composite_shape.deleteShape(1);
  printInfo(composite_shape);
  return 0;
}
