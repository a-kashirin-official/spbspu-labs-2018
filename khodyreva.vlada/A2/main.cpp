#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

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
  }
  catch(std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}
