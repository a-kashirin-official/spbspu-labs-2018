#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  Rectangle objRectangle({40,9,5,1});
  Circle objCircle(7,{4,2});
  std::cout << "Rectangle's area = " << objRectangle.getArea() << std::endl;
  objRectangle.move({32,43});
  std::cout << "New Rectangle's centre is (" << objRectangle.getFrameRect().pos.x << ";" << objRectangle.getFrameRect().pos.y << ")" << std::endl;
  objRectangle.move(12,33);
  std::cout << "New Rectangle's coordinates is (" << objRectangle.getFrameRect().pos.x << ";" << objRectangle.getFrameRect().pos.y << ")" << std::endl;
  std::cout << "****************************************************************" << std::endl;
  std::cout << "Circle's area = " << objCircle.getArea() << std::endl;
  std::cout << "Rectangle from the Circle: " << "width = " << objCircle.getFrameRect().width << " height = " << objCircle.getFrameRect().height << std::endl;
  objCircle.move({12,15});
  std::cout << "New Circle's centre is (" << objCircle.getFrameRect().pos.x << ";" << objCircle.getFrameRect().pos.y << ")" << std::endl;
  objCircle.move(25,71);
  std::cout << "New Circle's coordinates is (" << objCircle.getFrameRect().pos.x << ";" << objCircle.getFrameRect().pos.y << ")" << std::endl;
  return 0;
}
