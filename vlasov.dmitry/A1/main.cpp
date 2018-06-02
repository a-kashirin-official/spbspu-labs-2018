#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

int getRectInfo(Rectangle objrect)
{
  std::cout << "Rectangle height: " << objrect.getFrameRect().height << " ";
  std::cout << " , Width: " << objrect.getFrameRect().width << " ";
  std::cout << " and center(x,y): " << objrect.getFrameRect().pos.x << " ";
  std::cout << "," << objrect.getFrameRect().pos.y << std::endl;
  std::cout << "Rectangle's area: " << objrect.getArea() << std::endl;
  return 0;
};
 int getCircInfo(Circle objcircle)
 {
   std::cout << "Circle limit for height: " << objcircle.getFrameRect().height << " ";
   std::cout << " , limit for width: " << objcircle.getFrameRect().width << " ";
   std::cout << " and center(x,y)" << objcircle.getFrameRect().pos.x << " ";
   std::cout << "," << objcircle.getFrameRect().pos.y << std::endl;
   std::cout << "Circle's area: " << objcircle.getArea() << std::endl;
   return 0;
 }
int main()
{
  try {
    Rectangle objrect({5, 11, 3, 6});
    getRectInfo(objrect);
    Circle objcircle(3, {1, 1});
    getCircInfo(objcircle);
    objrect.move(3, 9);
    objcircle.move(5, 7);
    std::cout << "After first move:" << std::endl;
    getRectInfo(objrect);
    getCircInfo(objcircle);
    objcircle.move({10, 10});
    objrect.move({20, 20});
    std::cout << "After second move:" << std::endl;
    getRectInfo(objrect);
    getCircInfo(objcircle);
  } catch (std::invalid_argument & error) {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}
