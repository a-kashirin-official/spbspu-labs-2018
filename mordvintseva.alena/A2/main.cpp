#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

using namespace mordvintseva;
using std::cout;
using std::endl;
using std::cerr;

int main()
{
  try 
  {
    //Rectangle
    point_t pnt = { -5.0, 30.0 };
    rectangle_t initRect = { 20.0, 40.0, pnt };
    Rectangle rectangle = Rectangle(initRect);
    //Area
    cout << "Rectangle area: " << rectangle.getArea() << endl;
    //Frame Rectangle
    cout << "Rectangle: width = " << rectangle.getFrameRect().width << ", height = " << rectangle.getFrameRect().height << endl;
    cout << "   center: x = " << rectangle.getFrameRect().pos.x << ", y = " << rectangle.getFrameRect().pos.y << endl;
    //Move
    pnt = { 50.0, 80.0 };
    rectangle.move(pnt);
    cout << "Rectangle is moved" << endl;
    cout << "Rectangle: width = " << rectangle.getFrameRect().width << ", height = " << rectangle.getFrameRect().height << endl;
    cout << "   center: x = " << rectangle.getFrameRect().pos.x << ", y = " << rectangle.getFrameRect().pos.y << endl;
    //Scale
    rectangle.scale(0.5);
    cout << "Scale rectangle, factor = " << 0.5 << ":" << endl;
    cout << "Rectangle: width = " << rectangle.getFrameRect().width << ", height = " << rectangle.getFrameRect().height << endl;
    cout << "   center: x = " << rectangle.getFrameRect().pos.x << ", y = " << rectangle.getFrameRect().pos.y << endl;
    cout << endl;
  } catch (std::invalid_argument& e) {
    cerr << e.what() << endl;
  }
}
