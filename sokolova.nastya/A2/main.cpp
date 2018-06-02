#include "rectangle.hpp"
#include "circle.hpp"

#include <iostream>

using namespace sokolova;

int main()
{
  point_t centre{0.0, 6.0};
  Rectangle rect(centre, 2.0, 7.0);
  std::cout<<"Area of rectangle(rect) before scaling = "<<rect.getArea()<<std::endl;
  rect.scale(10.0);
  std::cout<<"Area of rectangle(rect) after scaling = "<<rect.getArea()<<std::endl;
  std::cout<<"Factor = 10"<<std::endl;
 
  Circle circ(centre, 1.5);
  std::cout<<"Area of Circle(circ) before scaling = "<<circ.getArea()<<std::endl;
  circ.scale(2.0);
  std::cout<<"Area of Circle(circ) after scaling = "<<circ.getArea()<<std::endl;
  std::cout<<"Factor = 2"<<std::endl;
 
  return 0;
}

