#include <iostream>
#include "base-types.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

using namespace std;

int main()
{
  //Rectangle
  point_t pnt = { 20.0, 30.0 };
  rectangle_t initRect = { 20.0, 40.0, pnt };
  Rectangle rectangle = Rectangle(initRect);
  //Area
  cout << "Rectangle area: " << rectangle.getArea() << endl;
  //Frame Rectangle
  cout << "Rectangle: width = " << rectangle.getFrameRect().width << ", height = " << rectangle.getFrameRect().height << endl;
  cout << "   center: x = " << rectangle.getFrameRect().pos.x << ", y = " << rectangle.getFrameRect().pos.y << endl;
  //move
  pnt = { 50.0, 80.0 };
  rectangle.move(pnt);
  cout << "Rectangle is moved" << endl;
  cout << "Rectangle: width = " << rectangle.getFrameRect().width << ", height = " << rectangle.getFrameRect().height << endl;
  cout << "   center: x = " << rectangle.getFrameRect().pos.x << ", y = " << rectangle.getFrameRect().pos.y << endl;
  cout << endl;

  //Circle
  pnt = { 40.0, 90.0 };
  Circle circle = Circle(20.0, pnt);
  //Area
  cout << "Circle area: " << circle.getArea() << endl;
  //Frame Rectangle
  cout << "Rectangle: width = " << circle.getFrameRect().width << ", height = " << circle.getFrameRect().height << endl;
  cout << "   center: x = " << circle.getFrameRect().pos.x << ", y = " << circle.getFrameRect().pos.y << endl;
  //move
  circle.move(10.0, -30.0);
  cout << "Circle is moved" << endl;
  cout << "Rectangle: width = " << circle.getFrameRect().width << ", height = " << circle.getFrameRect().height << endl;
  cout << "   center: x = " << circle.getFrameRect().pos.x << ", y = " << circle.getFrameRect().pos.y << endl;

  return 0;
}
