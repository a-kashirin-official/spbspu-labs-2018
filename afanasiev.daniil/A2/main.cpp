#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

using namespace afanasiev;

int main()
{
  Rectangle rect(10, 10, { 5, 5 } );
  std::cout << "Area (rect) before scale = " << rect.getArea() << std::endl;
  rect.scale(2);
  std::cout << "k = 2, Area (rect) after scale = " << rect.getArea() << std::endl;

  Circle circ({ 10, 10 }, 5);
  std::cout << "Area (circle) before scale = " << circ.getArea() << std::endl;
  circ.scale(2);
  std::cout << "k = 2, Area (circle) after scale = " << circ.getArea() << std::endl;
  return 0;
}
