#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include <iostream>

using namespace egorov;

int main()
{
  std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle(2.0, {3.0, 2.0}));
  std::shared_ptr<Shape> rectangle2 = std::make_shared<Rectangle>(Rectangle({10.0, 20.0, {1.0, 10.0}}));

  CompositeShape compositeShape;
  compositeShape.addShape(circle1);
  compositeShape.addShape(rectangle2);

  std::cout << compositeShape.getArea() << '\n' << compositeShape.getFrameRect().height
  << " " << compositeShape.getFrameRect().width << '\n' << compositeShape.getQuantity()
  << '\n';

  compositeShape.move({5.4, 6.0});
  compositeShape.move(2.0, 2.0);
  std::cout << "After move" << '\n' << compositeShape.getFrameRect().pos.x << " "
  << compositeShape.getFrameRect().pos.y
  << '\n';

  compositeShape.scale(2.0);

  std::cout << "After scale" << '\n';
  std::cout << compositeShape.getArea() << '\n' << compositeShape.getFrameRect().height
  << " " << compositeShape.getFrameRect().width << '\n' << compositeShape.getQuantity()
  << '\n';

  compositeShape.removeShape(0);
  std::cout << "After remove" << '\n';
  std::cout << compositeShape.getArea() << '\n' << compositeShape.getFrameRect().height
  << " " << compositeShape.getFrameRect().width << '\n' << compositeShape.getQuantity()
  << '\n';

  return 0;
}
