#include <iostream>
#include "base-types.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

using namespace std;

void printResults(const Shape & s)
{
  cout << "  Area is " << s.getArea() << endl;
  rectangle_t r = s.getFrameRect();
  cout << "  Frame rectangle has width - " << r.width << ", height - " << r.height << endl;
  cout << "    Center is in (" << r.pos.x << ", " << r.pos.y << ')' << endl;
}

int main(){

  Rectangle rect(6.9, 7.3, {8.5, 2.5});
  rect.printRect();
  printResults(rect);

  cout << "Moving rectangle to point (60,30)" << endl;
  rect.move({60, 30});
  rect.printRect();

  cout << "Moving rectangle by dx = 10 dy = 9" << endl;
  rect.move(10, 9);
  rect.printRect();

  cout << endl;

  Circle circ({10, 20}, 5);
  circ.printCircle();
  printResults(circ);

  cout << "Moving Circle to point (40,30) " << endl;
  circ.move({40, 30});
  circ.printCircle();

  cout << "Moving Circle by dx = 7 dy = 10 " << endl;
  circ.move(7, 10);
  circ.printCircle();

  return 0;
}
