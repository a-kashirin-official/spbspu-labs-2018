#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

using std::cin;
using std::cout;
using std::endl;

void printShapeInfo(const Shape & target)
{
  rectangle_t temp_data = target.getFrameRect();
  cout << "------------------------------------------------------" << endl;
  cout << "Area: " << target.getArea() << endl;
  cout << "      Center:" << endl;
  cout << "           x = " << temp_data.pos.x << endl;
  cout << "           y = " << temp_data.pos.y << endl;
  cout << "      Other Info:" << endl;
  cout << "       width = " << temp_data.width << endl;
  cout << "      height = " << temp_data.height << endl;
  cout << "------------------------------------------------------" << endl;
}

int main()
{
  Circle circ{{10.0, 15.0}, 5.0};

  cout << "CIRCLE" << endl;
  printShapeInfo(circ);
  cout << "MOVED CIRCLE" << endl;
  circ.move(33.0, 50.0);
  printShapeInfo(circ);


  Rectangle rect{{{40.0, 40.0}, 15.0, 15.0}};

  cout << "RECTANGLE" << endl;
  printShapeInfo(rect);
  cout << "MOVED RECTANGLE" << endl;
  rect.move(20.0, 20.0);
  printShapeInfo(rect);

  return 0;
}
