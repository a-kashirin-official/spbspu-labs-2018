#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

using namespace astafev;

int main()
{
  Circle Circle1({ 10.0, 10.0 }, 10.0);
  std::cout << "Area before scale = " << Circle1.getArea() << std::endl;
  Circle1.scale(0.5);
  std::cout << "k = 0.5, Area after scale = " << Circle1.getArea() << std::endl;

  Rectangle Rectangle1({ 0.0, 0.0 }, 4.0, 6.0);
  std::cout << "Area before scale = " << Rectangle1.getArea() << std::endl;
  Rectangle1.scale(2.5);
  std::cout << "koficent = 2.5, Area after scale = " << Rectangle1.getArea() << std::endl;

  return 0;
}

