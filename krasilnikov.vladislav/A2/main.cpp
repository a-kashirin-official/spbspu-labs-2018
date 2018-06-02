#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

using namespace krasilnikov;

int main()
{
  Rectangle rect(13, 13, {7, 7});
  std::cout << "Area (rectangle) before scale = " << rect.getArea() <<std::endl;
  rect.scale(5);
  std::cout << "k = 5, Area (rectangle) after scale = " << rect.getArea() << std::endl;

  Circle circ ({7, 7}, 13);
  std::cout << "Area (circle) before scale = " << rect.getArea() <<std::endl;
  rect.scale(5);
  std::cout << "k = 5, Area (circle) after scale = " << rect.getArea() << std::endl;

  return 0;
}
