#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix-shape.hpp"
#include <iostream>

using namespace egorov;

int main()
{
  try{
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
  compositeShape.rotate(90);

  std::cout << "After scale" << '\n';
  std::cout << compositeShape.getArea() << '\n' << compositeShape.getFrameRect().height
  << " " << compositeShape.getFrameRect().width << '\n' << compositeShape.getQuantity()
  << '\n';
  compositeShape.removeShape(1);

  MatrixShape matrixShape;
  matrixShape.addShape(circle1);
  matrixShape.addShape(rectangle2);
  std::shared_ptr<Shape> rectangle3 = std::make_shared<Rectangle>(Rectangle({5.0, 1.0, {1.0, 10.0}}));
  matrixShape.addShape(rectangle3);
  std::shared_ptr<Shape> rectangle4 = std::make_shared<Rectangle>(Rectangle({compositeShape.getFrameRect().width,
  compositeShape.getFrameRect().height, {compositeShape.getFrameRect().pos.x,
  compositeShape.getFrameRect().pos.y}}));
  matrixShape.addShape(rectangle4);
  matrixShape.printInfo();

} catch (const std::invalid_argument & error)
  {
     std::cerr << error.what() << '\n';
     return 1;
  }

  return 0;
}
