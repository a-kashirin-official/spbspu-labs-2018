#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

using namespace khodyreva;

int main()
{
  try
  {
    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({3.0, 2.0}, 5.0, 7.0));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({-10.0, 7.0}, 3.0, 6.0));
    std::shared_ptr<Shape> circ = std::make_shared<Circle>(Circle({2.0, 3.0}, 3.0));
    std::shared_ptr<Shape> rect33 = std::make_shared<Rectangle>(Rectangle({5.0, 4.0}, 1.0, 3.0));
    CompositeShape compShape(rect1);
    compShape.addShape(rect2);
    compShape.addShape(circ);
    std::cout << "Composite shape area is " << compShape.getArea() << std::endl;
    std::cout << "Composite shape size is" << compShape.getSize() << std::endl;
    std::cout << "Width of frame rectangle is " << compShape.getFrameRect().width << std::endl;
    std::cout << "Height of frame rectangle is " << compShape.getFrameRect().height << std::endl;
    compShape.scale(2.0);
    std::cout << "After scaling: " << std::endl;
    std::cout << "Composite shape area is " << compShape.getArea() << std::endl;
    compShape.move({5.0, 17.0});
    std::cout << "After moving to a certain point: " << std::endl;
    std::cout << "Width of frame rectangle is " << compShape.getFrameRect().width << std::endl;
    std::cout << "Height of frame rectangle is " << compShape.getFrameRect().height << std::endl;
    compShape.move(5.0, 17.0);
    std::cout << "After relative moving: " << std::endl;
    std::cout << "Width of frame rectangle is " << compShape.getFrameRect().width << std::endl;
    std::cout << "Height of frame rectangle is " << compShape.getFrameRect().height << std::endl;
    compShape.deleteShape(0);
    std::cout << "After deleting the first figure: " << std::endl;
    std::cout << "Composite shape area is " << compShape.getArea() << std::endl;
    std::cout << "Composite shape size is" << compShape.getSize() << std::endl;
    std::cout << "Width of frame rectangle is " << compShape.getFrameRect().width << std::endl;
    std::cout << "Height of frame rectangle is " << compShape.getFrameRect().height << std::endl;
    CompositeShape compShape2(rect1);
    compShape2.addShape(rect2);
    compShape2.addShape(rect33);
    compShape2.rotate(45.0);
    std::cout << "After rotation: " << std::endl;
    std::cout << "Width of frame rectangle is " << compShape2.getFrameRect().width << std::endl;
    std::cout << "Height of frame rectangle is " << compShape2.getFrameRect().height << std::endl;
    std::cout << "Composite shape area is " << compShape2.getArea() << std::endl;

    Matrix matrix(rect1);
    matrix.addShape(rect2);
    matrix.addShape(circ);
    std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({7.0, 1.0}, 5.0, 3.0));
    matrix.addShape(rect3);
    std::shared_ptr<Shape> rect4 = std::make_shared<Rectangle>(Rectangle({compShape.getFrameRect().pos.x,
    compShape.getFrameRect().pos.y}, compShape.getFrameRect().height,
    compShape.getFrameRect().width));
    matrix.addShape(rect4);
    matrix.printInfo();

  }
  catch(std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}
