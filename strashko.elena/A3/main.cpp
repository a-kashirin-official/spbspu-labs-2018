#include <iostream>
#include <memory>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace strashko;

void printFrameRect(const  Shape &sh, const char *name);
void printArea(const  Shape &sh, const char *name);

int main()
{
  point_t centre{ 6, 4 };
  point_t newpos{ -1, 6 };
  double factor = 7.04;

  Circle circle(centre, 18.2);
  std::shared_ptr< Shape > circlePtr = std::make_shared< Circle >(circle);
  printArea(circle, "Circle ");
  printFrameRect(circle, "Circle ");
  circle.move(newpos);
  printFrameRect(circle, "Circle ");
  circle.move(-3, 12);
  printFrameRect(circle, "Circle ");
  circle.scale(factor);
  printFrameRect(circle, "Circle");
  printArea(circle, "Circle ");

  std::cout << std::endl;

  Rectangle rectangle(centre, 8, 11);
  std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rectangle);
  printArea(rectangle, "Rectangle ");
  rectangle.move(newpos);
  printFrameRect(rectangle, "Rectangle ");
  rectangle.move(5, -6);
  printFrameRect(rectangle, "Rectangle ");
  rectangle.scale(factor);
  printFrameRect(rectangle, "Rectangle");
  printArea(rectangle, "Rectangle ");

  std::cout << std::endl;

  CompositeShape comp(circlePtr);
  printArea(comp, "CompositeShape ");
  comp.addShape(rectPtr);
  printFrameRect(comp, "CompositeShape ");
  comp.scale(factor);
  printFrameRect(comp, "CompositeShape ");
  printArea(comp, "CompositeShape ");
  comp.removeShape(1);
  printFrameRect(comp, "CompositeShape ");
  comp.deleteAllShapes();
  printFrameRect(comp, "CompositeShape ");

  return 0;
}

void printFrameRect(const Shape &sh, const char *name)
{
  rectangle_t framerect = sh.getFrameRect();
  std::cout << "FrameRect " << name << std::endl
      << "pos.x " << framerect.pos.x
      << " pos.y " << framerect.pos.y
      << " width " << framerect.width
      << " height " << framerect.height<< std::endl;
}

void printArea(const Shape &sh, const char *name)
{
  std::cout << "Area " << name <<" "
      << sh.getArea() << std::endl;
}
