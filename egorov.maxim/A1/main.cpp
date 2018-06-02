#include "circle.hpp"
#include "rectangle.hpp"
#include <iostream>

int main()
{
  Rectangle rect({10,20,{3,2}});
  std::cout << "Rectangle:\n";
  std::cout << rect.getArea() << '\n';
  std::cout << rect.getFrameRect().height << '\n' << rect.getFrameRect().width << '\n' <<
  rect.getFrameRect().pos.x << ' ' << rect.getFrameRect().pos.y << '\n';
  rect.move({10,2.5});
  std::cout << rect.getFrameRect().pos.x << ' ' << rect.getFrameRect().pos.y << '\n';
  rect.move(5,6);
  std::cout << rect.getFrameRect().pos.x << ' ' << rect.getFrameRect().pos.y << '\n' << '\n';

  Circle circ(2,{3,2});
  std::cout << "Circle:\n";
  std::cout << circ.getArea() << '\n';
  std::cout << circ.getFrameRect().height << '\n' << circ.getFrameRect().width << '\n' <<
  circ.getFrameRect().pos.x << ' ' << rect.getFrameRect().pos.y << '\n';
  circ.move({12,6.5});
  std::cout << circ.getFrameRect().pos.x << ' ' << circ.getFrameRect().pos.y << '\n';
  circ.move(10,3);
  std::cout << circ.getFrameRect().pos.x << ' ' << circ.getFrameRect().pos.y << '\n';

  return 0;
}
