#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  try
  {
    spodeneyko::Rectangle rect({24.0, 48.0, {128.0, 256.0}});
    spodeneyko::Shape * shapePtr = &rect;
    std::cout << "Rectangle:" << std::endl;
    std::cout << "Area of Rectangle before scaling = " << shapePtr -> getArea() << std::endl;
    shapePtr -> scale(2.0);
    std::cout << "Area of Rectangle after scaling = " << shapePtr -> getArea() << std::endl;
    std::cout << std::endl;

    spodeneyko::Circle circle(5.0, {10.0, 10.0});
    shapePtr = &circle;
    std::cout << "Circle:" << std::endl;
    std::cout << "Area of Circle before scaling = " << shapePtr -> getArea() << std::endl;
    shapePtr -> scale(3.0);
    std::cout << "Area of Circle after scaling = " << shapePtr -> getArea() << std::endl;
  }
  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}
