#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include <iostream>

using namespace gusev;

int main()
{
  Rectangle rect(10, 5, { 3, 4 });
  Circle circ(1, { 5, 5 });
  Triangle triang({ 1, 1 }, { -5, 1 }, { 4, 3 });

  try {
    std::cout << "Rectangle" << std::endl;
    std::cout << "Area=" << rect.getArea() << std::endl;
    rect.scale(3);
    std::cout << "scale(3)" << std::endl;
    std::cout << "Area=" << rect.getArea() << std::endl;

    std::cout << "Triangle" << std::endl;
    std::cout << "Area=" << triang.getArea() << std::endl;
    triang.scale(2);
    std::cout << "scale(2)" << std::endl;
    std::cout << "Area=" << triang.getArea() << std::endl;

    std::cout << "Circle" << std::endl;
    std::cout << "Area=" << circ.getArea() << std::endl;
    circ.scale(3);
    std::cout << "scale(3)" << std::endl;
    std::cout << "Area=" << circ.getArea() << std::endl;
  }
  catch(const std::invalid_argument &e) {
    std::cerr << e.what() <<std::endl;
    return 1;
  }
  return 0;
}
