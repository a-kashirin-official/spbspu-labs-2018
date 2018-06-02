#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace khodyreva;

int main()
{
  try
  {
    point_t rec_point = {19, 17};
    Rectangle rectangle(rec_point, 50, 70);
    point_t cir_point = {10, 11};
    Circle circle(cir_point, 10);
    std::cout << "Rectangle area is " << rectangle.getArea() << std::endl;
    std::cout << "Circle area is " << circle.getArea() << std::endl;
    const double ratio = 3.0;
    std::cout << "After scaling : " << std::endl;
    circle.scale(ratio);
    rectangle.scale(ratio);
    std::cout << "Rectangle area is " << rectangle.getArea() << std::endl;
    std::cout << "Circle area is " << circle.getArea() << std::endl;

    std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({3.0, 2.0}, 5.0, 7.0));
    std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({-10.0, 7.0}, 3.0, 6.0));
    std::shared_ptr<Shape> circ = std::make_shared<Circle>(Circle({2.0, 3.0}, 3.0));
    CompositeShape compShape(rect1);
    compShape.addShape(rect2);
    compShape.addShape(circ);
    std::cout << "Composite shape area is " << compShape.getArea() << std::endl;
    std::cout << "Composite shape size is" << compShape.getSize() << std::endl;
    std::cout << "Width of frame rectangle is " << compShape.getFrameRect().width << std::endl;
    std::cout << "Height of frame rectangle is " << compShape.getFrameRect().height << std::endl;
    compShape.scale(ratio);
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
  }
  catch(std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}
