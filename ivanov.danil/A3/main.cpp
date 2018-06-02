#include <iostream>

#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

using namespace ivanov;

int main()
{
  std::shared_ptr<Shape> Rectangle1 = std::make_shared<Rectangle>(Rectangle({7.9, 8.2, {-1.6, -2.0}}));
  std::shared_ptr<Shape> Circle1 = std::make_shared<Circle>(Circle({3.2, 2.6}, 6.9));
  std::shared_ptr<Shape> Rectangle2 = std::make_shared<Rectangle>(Rectangle({7.1, 4.09, {7.2, 2.6}}));
  std::shared_ptr<Shape> Circle2 = std::make_shared<Circle>(Circle({3.5, 5.6}, 5.5));

  CompositeShape compositeShape = CompositeShape();
  compositeShape.addShape(Rectangle1);
  compositeShape.addShape(Circle1);
  compositeShape.addShape(Rectangle2);
  compositeShape.addShape(Circle2);
  compositeShape.printInfo();

  compositeShape.scale(7.3);
  std::cout << "Scale on 7.3" << std::endl;
  compositeShape.printInfo();

  compositeShape.move({5.6, 7.8});
  std::cout << "Move to (5.6, 7.8) "<< std::endl;
  compositeShape.printInfo();

  compositeShape.move(-9.3, 8.7);
  std::cout << "Move on dx = -9.3, dy = 8.7" << std::endl;
  compositeShape.printInfo();

  compositeShape.deleteShape(0);
  std::cout << "Deleted shape[0] " << std::endl;
  compositeShape.printInfo();

  return 0;
}
