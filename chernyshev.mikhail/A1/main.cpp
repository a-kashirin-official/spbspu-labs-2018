#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

void printInfo(Shape &shape)
{
  std::cout<<"Pos (x,y): (" << shape.getFrameRect().pos.x << "," << shape.getFrameRect().pos.y << ")" <<std::endl;
  std::cout<<"Area "<<shape.getArea()<<std::endl;
  std::cout<<"Width "<<shape.getFrameRect().width<<std::endl;
  std::cout<<"Heigt "<<shape.getFrameRect().height<<std::endl;
}

int main()
{
  Rectangle rectangle(10,20,{10,20});
  std::cout<<"Rectangle"<<std::endl;
  printInfo(rectangle);
  point_t newCenter0 = {2,8};
  rectangle.Move(newCenter0.x,newCenter0.y);
  rectangle.Move(newCenter0);
  std::cout<<"Rectangle now: "<<std::endl;
  printInfo(rectangle);
    
  Circle cir(10, {10.0 , 15.0});
  std::cout<<"Circle"<<std::endl;
  printInfo(cir);
  point_t newCenter = {2,8};
  cir.Move(newCenter.x,newCenter.y);
  cir.Move(newCenter);
  std::cout<<"Circle now: "<<std::endl;
  printInfo(cir);
    
  Triangle triangle({10,10},{11,11},{12,10});
  std::cout<<"Triangle"<<std::endl;
  printInfo(triangle);
  point_t newCenter1 = {2,8};
  triangle.Move(newCenter1.x,newCenter1.y);
  triangle.Move(newCenter1);
  std::cout<<"Triangle now: "<<std::endl;
  printInfo(triangle);
    
    return 0;
}
