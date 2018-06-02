#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

void printInfo(Shape & shape)
{
  std::cout<<"  Width: "<<shape.getFrameRect().width<<std::endl;
  std::cout<<"  Height: "<<shape.getFrameRect().height<<std::endl;
  std::cout<<"  Area: "<<shape.getArea()<<std::endl;
  std::cout<<"  Pos(x, y): ("<<shape.getFrameRect().pos.x<<", "<<shape.getFrameRect().pos.y<<")"<<std::endl;
}

int main()
{
  Rectangle rectangle(4, 5, {0, 0});
  std::cout<<"Rectangle:"<<std::endl;
  printInfo(rectangle);
  point_t newCenter1 = {2, 8};
  rectangle.move(newCenter1);
  rectangle.move(5, 6);
  std::cout<<"Rectangle after movement:"<<std::endl;
  printInfo(rectangle);

  std::cout<<std::endl;

  Circle circle(1, {10,15});
  std::cout<<"Circle: "<<std::endl;
  printInfo(circle);
  point_t newCenter2 = {5, 8};
  circle.move(newCenter2);
  circle.move(1, 3);
  std::cout<<"Circle after movement: "<<std::endl;
  printInfo(circle);

  return 0;
}
