#include <iostream>

#include "circle.hpp"
#include "rectangle.hpp"

void printInfo(const Shape & shape)
{
  std::cout << "getArea = " << shape.getArea() << std::endl;
  const rectangle_t temp = shape.getFrameRect();
  std::cout << "FrameRect:" << std::endl;
  std::cout << "Mid = (" << temp.pos.x;
  std::cout << ", " << temp.pos.y << ")" << std::endl;
  std::cout << "Width = " << temp.width << " Height = " << temp.height << std::endl;
  std::cout << std::endl;
}

int main()
{
  const point_t point1{ 55.1, 101.4 };
  const double rad1 = 10.0;
  Shape * circ1 = nullptr;
  Shape * rect1 = nullptr;
  try {
  circ1 = new Circle(point1, rad1);
  rect1 = new Rectangle(10.2, 5.9, { 50.1, 18.3 } );

  std::cout << "Circle:" << std::endl;
  printInfo(*circ1);
  circ1->move(105.7, 15.6);
  printInfo(*circ1);
  delete circ1;

  std::cout << "Rectangle:" << std::endl;
  printInfo(*rect1);
  rect1->move(point1);
  printInfo(*rect1);
  delete rect1;
  } catch (std::bad_alloc & b) {
    delete circ1;
    delete rect1;
    std::cerr << b.what() << std::endl;
    return 2;
  } catch(std::invalid_argument & i) {
    std::cerr << i.what() << std::endl;
    delete circ1;
    delete rect1;
    return 1;
  }
  return 0;
}
