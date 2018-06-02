#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "base-types.hpp"
using namespace std;

int main()
{
  //13534/6 gruppa!!!
  std::cout << std::endl;
  std::cout << "Creating Rectangle x=14.0, y=19.0, w=3.0, h=5.0" << std::endl;
  point_t pnt = { 14.0, 19.0 };
  Rectangle rectangle = Rectangle(pnt, 3.0, 5.0);
  cout << "Rectangle area: " << rectangle.getArea() << endl;
  //Frame Rectangle
  std::cout << "Rectangle width = " << rectangle.getFrameRect().width << ", height = " << rectangle.getFrameRect().height << std::endl;
  std::cout << "  Rectangle center: x = " << rectangle.getFrameRect().pos.x << ", y = " << rectangle.getFrameRect().pos.y << std::endl;
  //move
  pnt = { 50.0, 80.0 };
  std::cout << "Rectangle is moved" << std::endl;
  rectangle.move(pnt);
  std::cout << "Rectangle: width = " << rectangle.getFrameRect().width << ", height = " << rectangle.getFrameRect().height << std::endl;
  std::cout << "  center: x = " << rectangle.getFrameRect().pos.x << ", y = " << rectangle.getFrameRect().pos.y << std::endl;
  std::cout << std::endl;

  //circle
  pnt = { 40.0, 90.0 };
  Circle circle = Circle(pnt, 20.0);
  //Area
  std::cout << "Circle area: " << circle.getArea() << std::endl;
  //Frame Rectangle
  std::cout << "Rectangle: width = " << circle.getFrameRect().width << ", height = " << circle.getFrameRect().height << std::endl;
  std::cout << "   center: x = " << circle.getFrameRect().pos.x << ", y = " << circle.getFrameRect().pos.y << std::endl;
  //move
  circle.move(10.0, -30.0);
  std::cout << "Circle is moved" << std::endl;
  std::cout << "Rectangle: width = " << circle.getFrameRect().width << ", height = " << circle.getFrameRect().height << std::endl;
  std::cout << "   center: x = " << circle.getFrameRect().pos.x << ", y = " << circle.getFrameRect().pos.y << std::endl;

  return 0;
}
