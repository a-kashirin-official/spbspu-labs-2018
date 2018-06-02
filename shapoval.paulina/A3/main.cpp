#include <iostream>
#include <memory>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

void printFrameRect(const shapoval::Shape & object)
{
  const shapoval::rectangle_t frame = object.getFrameRect();
  std::cout << "Centre: " << frame.pos.x << ", " << frame.pos.y << std::endl;
  std::cout << "Height: " << frame.height << std::endl;
  std::cout << "Width: " << frame.width << std::endl;
}

void printArea(const shapoval::Shape & object)
{
  std::cout << "Area: " << object.getArea() << std::endl;
}

int main()
{
  shapoval::Circle new_circle({0,0}, 10);

  std::cout << "CIRCLE  " << std::endl;
  std::cout << "~~Start circleFrameRect parameters~~ " << std::endl;
  printArea(new_circle);
  printFrameRect(new_circle);
  std::cout << "~~Expand the circle in 5 times~~ " << std::endl;
  new_circle.scale(5);
  printFrameRect(new_circle);
  printArea(new_circle);
  new_circle.move(10, 20);
  std::cout << "~~Move to x, y~~ " << std::endl;
  printFrameRect(new_circle);
  new_circle.move({20, 10});
  std::cout << "~~Move to point~~ " << std::endl;
  printFrameRect(new_circle);

  shapoval::Rectangle new_rectangle({0,0}, 10, 20);

  std::cout << "RECTANGLE  " << std::endl;
  std::cout << "~~Start rectangle parameters~~ " << std::endl;
  printArea(new_rectangle);
  printFrameRect(new_rectangle);
  std::cout << "~~Expand the rectangle in 5 times~~ " << std::endl;
  new_rectangle.scale(5);
  printFrameRect(new_rectangle);
  printArea(new_rectangle);
  new_rectangle.move(10, 20);
  std::cout << "~~Move to x, y~~" << std::endl;
  printFrameRect(new_rectangle);
  new_rectangle.move({20, 10});
  std::cout << "~~Move to point~~" << std::endl;
  printFrameRect(new_rectangle);

  std::shared_ptr <shapoval::Shape> new_circlePtr = std::make_shared <shapoval::Circle> (new_circle);
  std::shared_ptr <shapoval::Shape> new_rectanglePtr = std::make_shared <shapoval::Rectangle> (new_rectangle);
  shapoval::CompositeShape new_compositeshape(new_circlePtr);


  std::cout << "COMPOSITE SHAPE  " << std::endl;
  std::cout << "~~Start composite shape parameters~~" << std::endl;
  printArea(new_compositeshape);
  printFrameRect(new_compositeshape);
  std::cout << "~~Add rectangle in composite shape~~" << std::endl;
  new_compositeshape.addShape(new_rectanglePtr);
  printArea(new_compositeshape);
  printFrameRect(new_compositeshape);

  shapoval::CompositeShape CoSh = std::move(new_compositeshape);
  printArea(CoSh);
  printFrameRect(CoSh);
  shapoval::CompositeShape new_compositeshape1 = CoSh;
  shapoval::CompositeShape new_compositeshape2 = new_compositeshape1;
  CoSh.removeShape(1);
  std::cout << "~~equality~~" << std::endl;
  printFrameRect(new_compositeshape1);
  printFrameRect(CoSh);
  new_compositeshape2 = std::move(CoSh);
  printFrameRect(new_compositeshape2);
  printFrameRect(CoSh);

  std::cout << "~~Expend composite shape in 5 times~~" << std::endl;
  new_compositeshape1.scale(5);
  printArea(new_compositeshape1);
  printFrameRect(new_compositeshape1);
  std::cout << "~~Remove circle from composite shape~~" << std::endl;
  new_compositeshape1.removeShape(1);
  printArea(new_compositeshape1);
  printFrameRect(new_compositeshape1);
  std::cout << "~~Delete all shapes~~" << std::endl;
  new_compositeshape1.deleteShapes();
  printArea(new_compositeshape1);
  printFrameRect(new_compositeshape1);

  return 0;
}
