#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

using namespace ponomarev;

int main()
{
  std::shared_ptr<Shape> rectangle1 = std::make_shared<Rectangle>(Rectangle({-4.0, -4.0}, 3.0, 3.0));
  std::shared_ptr<Shape> rectangle2 = std::make_shared<Rectangle>(Rectangle({-1.0, -1.0}, 2.0, 2.0));
  std::shared_ptr<Shape> rectangle3 = std::make_shared<Rectangle>(Rectangle({1.0, 1.0}, 3.0, 3.0));

  CompositeShape compositeShape;
  compositeShape.addShape(rectangle1);
  compositeShape.addShape(rectangle2);
  compositeShape.addShape(rectangle3);

  std::cout << "area of composite shape = " << compositeShape.getArea() << std::endl
            << "width of frame rect = " << compositeShape.getFrameRect().width << std::endl
            << "height of frame rect = " << compositeShape.getFrameRect().height << std::endl
            << "Quantity of shapes in array = " << compositeShape.getQuantity() << std::endl << std::endl;

  compositeShape.scale(2);

  std::cout << "scale with coefficient = 2.0" << std::endl
            << "area of composite shape = " << compositeShape.getArea() << std::endl
            << "width of frame rect = " << compositeShape.getFrameRect().width << std::endl
            << "height of frame rect = " << compositeShape.getFrameRect().height << std::endl
            << "quantity of shapes in array = " << compositeShape.getQuantity() << std::endl << std::endl;

  compositeShape.move({3.0, 2.0});
  compositeShape.move(3.0, 3.0);

  std::cout << "move to x = 3.0, y = 2.0 \t" << "move on x = 3.0, y = 3.0" << std::endl
            << "at now x = " << compositeShape.getFrameRect().pos.x
            << " y = " << compositeShape.getFrameRect().pos.y << std::endl << std::endl;

  compositeShape.removeShape(1);
  compositeShape.removeShape(0);

  std::cout << "first and second figures has been removed " << std::endl;
  std::cout << "area of composite shape = " << compositeShape.getArea() << std::endl
            << "width of frame rect = " << compositeShape.getFrameRect().width << std::endl
            << "height of frame rect = " << compositeShape.getFrameRect().height << std::endl
            << "quantity of shapes in array = " << compositeShape.getQuantity() << std::endl << std::endl;
  return 0;
}
