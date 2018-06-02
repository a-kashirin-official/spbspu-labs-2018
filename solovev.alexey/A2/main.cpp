#include "rectangle.hpp"
#include <iostream>
#include "circle.hpp"

using namespace solovev;

void printInf( Shape & shape)
{
  std::cout<<"Area: "<<shape.getArea()<<std::endl;
  std::cout<<"Position of center: ("<<shape.getFrameRect().pos.x<<", "<<shape.getFrameRect().pos.y<<")"<<std::endl;
  std::cout<<"Width of rectangle frame: "<<shape.getFrameRect().width<<std::endl;
  std::cout<<"Height of rectangle frame: "<<shape.getFrameRect().height<<std::endl;
}

int main()
{
  Rectangle rect = Rectangle({5, 4}, 100, 50);
  Circle circ = Circle(20, {5, 5});

  std::cout<<"Before scaling:"<<std::endl;
  std::cout<<"Rectangle"<<std::endl;
  printInf(rect);
  std::cout<<"Rectangle"<<std::endl;
  printInf(circ);

  std::cout<<"After scaling:"<<std::endl;

  rect.scale(2);
  circ.scale(3);
  std::cout<<"Rectangle"<<std::endl;
  printInf(rect);
  std::cout<<"Rectangle"<<std::endl;
  printInf(circ);
  return 0;
}
