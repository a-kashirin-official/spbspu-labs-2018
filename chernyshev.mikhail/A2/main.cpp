#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

namespace chernyshev
{
void printInfo(Shape &shape)
{
  std::cout<<"Pos (x,y): (" << shape.getFrameRect().pos.x << "," << shape.getFrameRect().pos.y << ")" <<std::endl;
  std::cout<<"Area "<<shape.getArea()<<std::endl;
  std::cout<<"Width "<<shape.getFrameRect().width<<std::endl;
  std::cout<<"Heigt "<<shape.getFrameRect().height<<std::endl;
}
}
int main()
{
  try
  {
    chernyshev::Rectangle rectangle(10,20,{10,20});
    std::cout<<"Rectangle"<<std::endl;
    chernyshev::printInfo(rectangle);
    chernyshev::point_t newCenter0 = {2,8};
    rectangle.Move(newCenter0.x,newCenter0.y);
    rectangle.Move(newCenter0);
    std::cout<<"Rectangle now: "<<std::endl;
    chernyshev::printInfo(rectangle);
    std::cout<<"Before Scale"<<std::endl;
    rectangle.printScale();
    std::cout<<"Ather Scale"<<std::endl;
    rectangle.scale(1.5);
    rectangle.printScale();
    
    std::cout<<std::endl;
    
    chernyshev::Circle circle(10, {10.0 , 15.0});
    std::cout<<"Circle"<<std::endl;
    chernyshev::printInfo(circle);
    chernyshev::point_t newCenter = {2,8};
    circle.Move(newCenter.x,newCenter.y);
    circle.Move(newCenter);
    std::cout<<"Circle now: "<<std::endl;
    chernyshev::printInfo(circle);
    std::cout<<"Before Scale"<<std::endl;
    circle.printScale();
    std::cout<<"After Scale"<<std::endl;
    circle.scale(1.5);
    circle.printScale();
    
    chernyshev::Triangle triangle({10,10},{11,11},{12,10});
    std::cout<<"Triangle"<<std::endl;
    chernyshev::printInfo(triangle);
    chernyshev::point_t newCenter1 = {2,8};
    triangle.Move(newCenter1.x,newCenter1.y);
    triangle.Move(newCenter1);
    std::cout<<"Triangle now: "<<std::endl;
    chernyshev::printInfo(triangle);
    std::cout<<"Before Scale"<<std::endl;
    triangle.printScale();
    std::cout<<"Ather Scale"<<std::endl;
    triangle.scale(1.5);
    triangle.printScale();
    
  }
  catch(std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
return 0;
}
