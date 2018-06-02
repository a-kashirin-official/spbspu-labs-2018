#include <iostream>

#include "circle.hpp"
#include "rectangle.hpp"

#include "composite-shape.hpp"
#include "matrix.hpp"

int main()
{
  try
  {
    std::shared_ptr<shalgueva::Shape> circ1 =
      std::make_shared<shalgueva::Circle>(shalgueva::Circle({1.0, 1.0}, 1.0));
    std::shared_ptr<shalgueva::Shape> circ2 =
      std::make_shared<shalgueva::Circle>(shalgueva::Circle({-5.0, -5.0}, 5.0));
    std::shared_ptr<shalgueva::Shape> rect1 =
      std::make_shared<shalgueva::Rectangle>(shalgueva::Rectangle({2.0, 2.0, {1.0, 1.0}}));
    std::shared_ptr<shalgueva::Shape> rect2 =
      std::make_shared<shalgueva::Rectangle>(shalgueva::Rectangle({2.0, 2.0, {3.0, 3.0}}));
    std::shared_ptr<shalgueva::Shape> rect3 =
      std::make_shared<shalgueva::Rectangle>(shalgueva::Rectangle({2.0, 2.0, {-6.0, 0.0}}));

    shalgueva::CompositeShape compositeShape(rect1);
    compositeShape.addShape(circ2);
    compositeShape.addShape(rect2);
    compositeShape.addShape(rect2);
    compositeShape.addShape(rect3);
    std::cout << "***" <<compositeShape.getFrameRect().pos.x << std::endl;
    std::cout << compositeShape.getFrameRect().pos.y << std::endl;

    std::cout<< "Move to (2,1)" << std::endl;
    compositeShape.move(2.0,1.0);

    std::cout<< "Scale 2" << std::endl;
    compositeShape.scale(2.0);

    std::cout<< "Rotate 90" << std::endl;
    compositeShape.rotate(-45.0);

    std::cout << compositeShape.getFrameRect().pos.x << std::endl;
    std::cout << compositeShape.getFrameRect().pos.y << std::endl;
    std::cout << compositeShape.getFrameRect().width << std::endl;
    std::cout << compositeShape.getFrameRect().height << std::endl;

    shalgueva::Matrix matrix(circ1);
    matrix.addShape(circ2);
    matrix.addShape(rect1);
    matrix.addShape(rect2);
    matrix.addShape(rect3);
    std::cout << "Quantity of layers" << std::endl;
    std::cout << matrix.getLayersNumber();
  }
  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  catch (std::out_of_range & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }

  return 0;
}

