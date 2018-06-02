#include <iostream>
#include <cmath>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace iliintsev;

int main() 
{
  Rectangle rect{{5.0, 5.0}, 5.0, 5.0};
  Circle circ{{10.0, 10.0}, 4.0};

  std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({5.0, 5.0}, 5.0, 5.0));
  std::shared_ptr<Shape> circ1 = std::make_shared<Circle>(Circle({10.0, 10.0}, 4.0));
  std::shared_ptr<Shape> circ2 = std::make_shared<Circle>(Circle({-4.0, -4.0}, 5.0));

  CompositeShape compShape;

  compShape.add(rect1);
  std::cout << "Rectangle" << std::endl;
  std::cout << rect.getArea() << std::endl;
  std::cout << compShape.getArea() << std::endl;

  compShape.add(circ1);
  std::cout << " Rectangle + Circle1 " << std::endl;
  double area = rect.getArea() + circ.getArea();
  std::cout << area << std::endl;
  std::cout << compShape.getArea() << std::endl;

  compShape.add(circ2);
  compShape.remove(1);
  std::cout << " Rectangle + Circle2 - Circle1 " << std::endl;
  area = rect.getArea() + M_PI * 5.0 * 5.0;
  std::cout << area << std::endl;
  std::cout << compShape.getArea() << std::endl;


  return(0);
}
