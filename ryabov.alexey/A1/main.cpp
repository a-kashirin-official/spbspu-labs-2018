#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "shape.hpp"

int main()
{
  Shape *rect1 = nullptr;
  Shape *rect2 = nullptr;
  Shape *circ1 = nullptr;

  try {
    rectangle_t frame = { 5, 5, { 10, 10 }};
    rect1 = new Rectangle(1, 4);
    rect2 = new Rectangle(frame);
    circ1 = new Circle(3.0);

    std::cout << "Area of rect1 is " << rect1->getArea() << std::endl;
    std::cout << "Position of rect1 is " << rect1->getFrameRect().pos.x << " " << rect1->getFrameRect().pos.y << std::endl;
    rect1->move(2, 4);
    std::cout << "Position of rect1 is " << rect1->getFrameRect().pos.x << " " << rect1->getFrameRect().pos.y << std::endl;

    std::cout << "Area of circle1 is " << circ1->getArea() << std::endl;
    std::cout << "Position of circle1 is " << circ1->getFrameRect().pos.x << " " << circ1->getFrameRect().pos.y << std::endl;
    circ1->move({10, 10});
    std::cout << "Position of circle1 is " << circ1->getFrameRect().pos.x << " " << circ1->getFrameRect().pos.y << std::endl;

    std::cout << "Area of rect2 is " << rect2->getArea() << std::endl;
    std::cout << "Position of rect2 is " << rect2->getFrameRect().pos.x << " " << rect2->getFrameRect().pos.y << std::endl;
    rect2->move(1, 2);
    std::cout << "Position of rect2 is " << rect2->getFrameRect().pos.x << " " << rect2->getFrameRect().pos.y << std::endl;
  }
  catch (const std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
    delete rect1;
    delete rect2;
    delete circ1;
    return 1;
  }
  catch (const std::bad_alloc &ba) {
    std::cerr << ba.what() << std::endl;
    delete rect1;
    delete rect2;
    delete circ1;
    return 2;
  }

  delete rect1;
  delete rect2;
  delete circ1;
  
  return 0;
}
