#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"


int main()
{
  point_t p {8.1 , 6.3};
  rectangle_t frame;

  Rectangle rectang = { 3.2, 4.2, p};

  std::cout<<"Rectangle"<<std::endl;
  std::cout<<"Width of rectangle="<<rectang.getWidth()<<std::endl;
  std::cout<<"Height of rectangle="<<rectang.getHeight()<<std::endl;
  std::cout<<"Centre rectangle("<<rectang.getCentre().x<<";"<<rectang.getCentre().y<<")"<<std::endl;
  double s = 0;
  s = rectang.getArea();
  std::cout<<"Area of rectangle="<<s<<std::endl;
  frame = rectang.getFrameRect();
  std::cout<<"Centre of FrameRectangle ("<<frame.pos.x<<";"<<frame.pos.y<<")"<<std::endl;
  p = { 4.1, 3.4 };
  std::cout<<"Coordinates of point ("<<p.x<<";"<<p.y<<")"<<std::endl;
  rectang.move(p);
  std::cout<<"Centre after movement to point ("<<rectang.getCentre().x<<";"<<rectang.getCentre().y<<")"<<std::endl;
  double dx = 7.0;
  double dy = 9.0;
  std::cout<<"X-movement="<<dx<<";"<<"Y-movement="<<dy<<std::endl;
  rectang.move(dx, dy);
  std::cout<<"Centre after moving by dx, dy ("<<rectang.getCentre().x<<";"<<rectang.getCentre().y<<")\n\n";

  p = {1.1, 2.4};

  Circle circ = { 2.1, p};
  std::cout<<"Circle"<<std::endl;
  std::cout<<"Centre circle("<<circ.getCentre().x<<";"<<circ.getCentre().y<<")"<<std::endl;
  s = circ.getArea();
  std::cout<<"Area of circle="<<s<<std::endl;
  frame = circ.getFrameRect();
  std::cout<<"Centre of FrameRectangle ("<<frame.pos.x<<";"<<frame.pos.y<<")"<<std::endl;
  p = {2.3, 1.2};
  std::cout<<"Coordinates of point ("<<p.x<<";"<<p.y<<")"<<std::endl;
  circ.move(p);
  std::cout<<"Centre after movement to point("<<circ.getCentre().x<<";"<<circ.getCentre().y<<")"<<std::endl;
  std::cout<<"X-movement="<<dx<<";"<<"Y-movement="<<dy<<std::endl;
  circ.move(dx, dy);
  std::cout<<"Centre after moving by dx, dy ("<<circ.getCentre().x<<";"<<circ.getCentre().y<<")\n\n";

  return 0;
}
