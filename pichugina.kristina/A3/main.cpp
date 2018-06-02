#include <iostream>
#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

void printInfo(const pichugina::Shape & object)
{
  std::cout << "Area: " << object.getArea() << std::endl;
  const pichugina::rectangle_t frame = object.getFrameRect();
  std::cout << "Frame for object:" << std::endl;
  std::cout << "Middle " << frame.pos.x << ", " << frame.pos.y << std::endl;
  std::cout << "Width " << frame.width << std::endl;
  std::cout << "Height " << frame.height << std::endl;
}

int main()
{
  pichugina::Circle circ{ { 3.31, 24.11 }, 10.41 };
  pichugina::Rectangle rect{ { 11.55, 2.24 }, 7.53, 6.81 };
  std::shared_ptr <pichugina::Shape> circ_n = std::make_shared <pichugina::Circle> (circ);
  std::shared_ptr <pichugina::Shape> rect_n = std::make_shared <pichugina::Rectangle> (rect);
  pichugina::CompositeShape composite_shape(circ_n);

  std::cout << "Composite shape parametrs " << std::endl;
  printInfo(composite_shape);
  std::cout << "Add rectangle in composite shape " << std::endl;
  composite_shape.addShape(rect_n);
  printInfo(composite_shape);

  pichugina::CompositeShape CompSh = std::move(composite_shape);
  printInfo(CompSh);
  pichugina::CompositeShape composite_shape_n = CompSh;
  pichugina::CompositeShape composite_shape_n2 = composite_shape_n;
  CompSh.removeShape(1);
  std::cout << "Equality " << std::endl;
  printInfo(composite_shape_n);
  printInfo(CompSh);
  composite_shape_n2 = std::move(CompSh);
  printInfo(composite_shape_n2);
  printInfo(CompSh);

  std::cout << "Expend composite shape in 3 times " << std::endl;
  composite_shape_n.scale(3);
  printInfo(composite_shape_n);
  std::cout << "Remove circle from composite shape " << std::endl;
  composite_shape_n.removeShape(1);
  printInfo(composite_shape_n);
  std::cout << "Delete all shapes " << std::endl;
  composite_shape_n.deleteShapes();
  printInfo(composite_shape_n);

  return 0;
}
