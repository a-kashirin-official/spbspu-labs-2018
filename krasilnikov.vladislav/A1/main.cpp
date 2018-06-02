#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"

void printInfo (const Shape & shape)
{
  std::cout << "getArea = " << shape.getArea() << std::endl;
  const rectangle_t tmp = shape.getFrameRect();
  std::cout << "FrameRect: " << std::endl;
  std::cout << "Middle = (" << tmp.pos.x << ", " << tmp.pos.y << ")" << std::endl;
  std::cout << "Height = " << tmp.height << std::endl;
  std::cout << "Width = " << tmp.width << std::endl;
  std::cout << std::endl;
}

int main()
{
  const point_t point1{119.0, 18.1};
  const double radius1 = 13.0;

  Shape * rectangle1 = nullptr;
  Shape * circle1 = nullptr;
  try {
    rectangle1 = new Rectangle(32.1, 43.2, {56.7, 67.8});
    circle1 = new Circle(point1, radius1);

    std::cout << "Rectangle: " << std::endl;
    printInfo(*rectangle1);
    rectangle1->move(14.18, 42.42);
    printInfo(*rectangle1);
    delete rectangle1;

    std::cout << "Circle: " << std::endl;
    printInfo(*circle1);
    circle1->move(point1);
    printInfo(*circle1);
    delete circle1;

  } catch(std::invalid_argument & invalid) {
    std::cerr << invalid.what() << std::endl;
    delete rectangle1;
    delete circle1;
    return 1;
  } catch (std::bad_alloc & bad) {
    std::cerr << bad.what() << std::endl;
    delete rectangle1;
    delete circle1;
    return 2;
  }

  return 0;
}
