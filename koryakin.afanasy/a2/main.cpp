#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

using namespace koryakin;
using std::cout;
using std::endl;
using std::cerr;

int main()
{
  try 
  {
    //Rectangle
    point_t pnt = { 14.0, 19.0 };
    Rectangle rectangle = Rectangle(pnt, 3.0, 5.0);
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
