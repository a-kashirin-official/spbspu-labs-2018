#include "rectangle.hpp"
#include "circle.hpp"
#include <iostream>

void test(Shape & obj) {
  std::cout << "Coordinates 1 are: " << obj.getFrameRect().pos.x << " and " << obj.getFrameRect().pos.y << std::endl;
  obj.move(2.39, 2.39);
  std::cout << "Coordinates 2 are: " << obj.getFrameRect().pos.x << " and " << obj.getFrameRect().pos.y << std::endl;
  obj.move({30.3, 50.5});
  std::cout << "Coordinates 3 are: " << obj.getFrameRect().pos.x << " and " << obj.getFrameRect().pos.y << std::endl;
  std::cout << "Figures width is " << obj.getFrameRect().width << std::endl;
  std::cout << "Figures height is " << obj.getFrameRect().height << std::endl;
  std::cout << "Figures area is " << obj.getArea() << std::endl;
  std::cout << "-------------------" << std::endl;
}

int main() {
  Rectangle testRect({45.5, 23.2}, 4.6, 5.6);
  Circle testCircle({76.5, 34.7}, 5.6);
  test(testRect);
  test(testCircle);
  return(0);
}
