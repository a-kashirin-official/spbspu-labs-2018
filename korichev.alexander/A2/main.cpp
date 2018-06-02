#include "rectangle.hpp"
#include "circle.hpp"

#include <iostream>

using namespace korichev;

void test(Shape & testerx)
{
  std::cout << "Area is: " << testerx.getArea() << std::endl;
  std::cout << "Current coordinates: (" << testerx.getFrameRect().pos.x << ", " << testerx.getFrameRect().pos.y<<')'<<std::endl;
  testerx.move(6,3);
  std::cout << "Coordinates (moved 6 3): (" << testerx.getFrameRect().pos.x << ", " << testerx.getFrameRect().pos.y<<')'<<std::endl;
  testerx.move({3.5,1.5});
  std::cout << "Coordinates (moved to (3.5,1.5)): (" << testerx.getFrameRect().pos.x << ", " << testerx.getFrameRect().pos.y<<')'<<std::endl;
  testerx.scale(2.0);
  std::cout << "Scaled shape by 2, current area: " << testerx.getArea() << std::endl;
}

int main()
{
  Circle circle_({5,5},3);
  Rectangle rectangle_({10,10},5,3);
  try
  {
    test(circle_);
    test(rectangle_);
  } catch ( std::invalid_argument & problem)
  {
    std::cerr << problem.what() << std::endl;
    return 1;
  }
  return 0;
}
