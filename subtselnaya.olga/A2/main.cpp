#include <iostream>
#include "base-types.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

using namespace std;
using namespace subtselnaya;

void printResults(const Shape & s)
{
  cout << "  Area is " << s.getArea() << endl;
  rectangle_t r = s.getFrameRect();
  cout << "  Frame rectangle has width - " << r.width << ", height - " << r.height << endl;
  cout << "    Center is in (" << r.pos.x << ", " << r.pos.y << ')' << endl;
}

int main(){

  Rectangle rect(6.9, 7.3, {8.5, 2.5});
  cout << "Rectangle has width - 6.9, height - 7.3" << std::endl;
  cout << "  Center is in (8.5, 2.5)" << std::endl;
  printResults(rect);

  cout << "Moving rectangle to point (60.3, 30.8)" << endl;
  rect.move({60.3, 30.8});

  cout << "Moving rectangle with dx = 10.0 dy = 9.6" << endl;
  rect.move(10.0, 9.6);

  cout << "Scaling rectangle with 3.8" << endl;
  rect.scale(3.8);

  cout << endl;

  Circle circ({10.6, 20.2}, 5.0);
  cout << "Circle has radius - 5.0" << std::endl;
  cout << "  Center is in (10.6, 20.2)" << std::endl;
  printResults(circ);

  cout << "Moving circle to point (40.0, 30.0) " << endl;
  circ.move({40.0, 30.0});

  cout << "Moving circle with dx = 7.4 dy = 10.7 " << endl;
  circ.move(7.4, 10.7);

  cout << "Scaling circle with 3.8" << endl;
  circ.scale(3.8);

  return 0;
}
