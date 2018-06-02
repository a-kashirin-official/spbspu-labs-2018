#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

using namespace mihajlov;

int main()
{
  std::shared_ptr<Shape> rectangle(new Rectangle({12.0, 18.0}, 10.0, 16.0));
  std::shared_ptr<Shape> circle(new Circle({0.0, 18.0}, 20));

  CompositeShape compositeShape1(rectangle);
  std::cout << "Created composite-shape with a single shape by default" << std::endl;
  compositeShape1.addShape(circle);
  std::cout << "Added second shape" << std::endl;
  compositeShape1.getInfo();
  std::cout << std::endl;

  CompositeShape compositeShape2;
  std::cout << "Created Empty composite-shape" << std::endl;
  compositeShape2.addShape(circle);
  std::cout << "Added another shape to second composite-shape" << std::endl;
  compositeShape2.getInfo();
  std::cout << std::endl;

  std::cout << "Composite-shape1 includes: " << std::endl;
  compositeShape1[0].getInfo();
  compositeShape1[1].getInfo();

  std::cout << std::endl << "Composite-shape2 includes: " << std::endl;
  compositeShape2[0].getInfo();

  return 0;
}
