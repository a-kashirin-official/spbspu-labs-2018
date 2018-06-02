#include <iostream>
#include <memory>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

void printFrameRect(const volkov::Shape & entity)
{
  const volkov::rectangle_t frame = entity.getFrameRect();
  std::cout << "Centre - " << frame.pos.x << ", " << frame.pos.y << std::endl;
  std::cout << "Height - " << frame.height << std::endl;
  std::cout << "Width - " << frame.width << std::endl;
}

void printArea(const volkov::Shape & entity)
{
  std::cout << "Area - " << entity.getArea() << std::endl;
}

int main()
{
  volkov::Circle circ( {0,0}, 1 );
  volkov::Rectangle rect( {0,0}, 1, 2 );
  std::shared_ptr <volkov::Shape> circ_n = std::make_shared <volkov::Circle> (circ);
  std::shared_ptr <volkov::Shape> rect_n = std::make_shared <volkov::Rectangle> (rect);
  volkov::CompositeShape composite_shape(circ_n);

  std::cout << "composite shape  " << std::endl;
  std::cout << "Start composite shape parameters " << std::endl;
  printArea(composite_shape);
  printFrameRect(composite_shape);
  std::cout << "Add rectangle in composite shape " << std::endl;
  composite_shape.addShape(rect_n);
  printArea(composite_shape);
  printFrameRect(composite_shape);

  volkov::CompositeShape CompSh = std::move(composite_shape);
  printArea(CompSh);
  printFrameRect(CompSh);
  volkov::CompositeShape composite_shape_n = CompSh;
  volkov::CompositeShape composite_shape_n2 = composite_shape_n;
  CompSh.removeShape(1);
  std::cout << "equality " << std::endl;
  printFrameRect(composite_shape_n);
  printFrameRect(CompSh);
  composite_shape_n2 = std::move(CompSh);
  printFrameRect(composite_shape_n2);
  printFrameRect(CompSh);

  std::cout << "Expend composite shape in 3 times " << std::endl;
  composite_shape_n.scale(3);
  printArea(composite_shape_n);
  printFrameRect(composite_shape_n);
  std::cout << "Remove circle from composite shape " << std::endl;
  composite_shape_n.removeShape(1);
  printArea(composite_shape_n);
  printFrameRect(composite_shape_n);
  std::cout << "Delete all shapes " << std::endl;
  composite_shape_n.deleteShapes();
  printArea(composite_shape_n);
  printFrameRect(composite_shape_n);

  return 0;
}
