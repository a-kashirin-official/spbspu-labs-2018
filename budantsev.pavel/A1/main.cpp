#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

int main()
{
  Rectangle objRectangle(40,9,{5,1});
  Circle objCircle(7,{4,2});
  Triangle objTriangle({2,5},{3,2},{0,1});

  std::cout<<"rectangle area is "<<objRectangle.getArea()<<std::endl;
  std::cout<<"circle area is "<<objCircle.getArea()<<std::endl;
  std::cout<<"triangle area is "<<objTriangle.getArea()<<std::endl<<std::endl;



  std::cout<<"rectangle centre is at ("<<objRectangle.getFrameRect().pos.x<<":"<<objRectangle.getFrameRect().pos.y<<")"<<std::endl;
  std::cout<<"circle centre is at ("<<objCircle.getFrameRect().pos.x<<":"<<objCircle.getFrameRect().pos.y<<")"<<std::endl;
  std::cout<<"triangle centre is at ("<<objTriangle.getCenterPoint().x<<":"<<objTriangle.getCenterPoint().y<<")"<<std::endl<<std::endl;

  objRectangle.move({4,20});
  objCircle.move({25,24.7});
  objTriangle.move({3,5});

  std::cout<<"moving shapes (teleporting)"<<std::endl<<std::endl;

  std::cout<<"rectangle area is "<<objRectangle.getArea()<<std::endl;
  std::cout<<"circle area is "<<objCircle.getArea()<<std::endl;
  std::cout<<"triangle area is "<<objTriangle.getArea()<<std::endl<<std::endl;

  std::cout<<"rectangle centre is at ("<<objRectangle.getFrameRect().pos.x<<":"<<objRectangle.getFrameRect().pos.y<<")"<<std::endl;
  std::cout<<"circle centre is at ("<<objCircle.getFrameRect().pos.x<<":"<<objCircle.getFrameRect().pos.y<<")"<<std::endl;
  std::cout<<"triangle centre is at ("<<objTriangle.getCenterPoint().x<<":"<<objTriangle.getCenterPoint().y<<")"<<std::endl<<std::endl;


  objRectangle.move(5,7);
  objCircle.move(2,1);
  objTriangle.move(7,5);

  std::cout<<"moving shapes by increment"<<std::endl<<std::endl;

  std::cout<<"rectangle area is "<<objRectangle.getArea()<<std::endl;
  std::cout<<"circle area is "<<objCircle.getArea()<<std::endl;
  std::cout<<"triangle area is "<<objTriangle.getArea()<<std::endl<<std::endl;

  std::cout<<"rectangle centre is at ("<<objRectangle.getFrameRect().pos.x<<":"<<objRectangle.getFrameRect().pos.y<<")"<<std::endl;
  std::cout<<"circle centre is at ("<<objCircle.getFrameRect().pos.x<<":"<<objCircle.getFrameRect().pos.y<<")"<<std::endl;
  std::cout<<"triangle centre is at ("<<objTriangle.getCenterPoint().x<<":"<<objTriangle.getCenterPoint().y<<")"<<std::endl<<std::endl;

  return 0;
}
