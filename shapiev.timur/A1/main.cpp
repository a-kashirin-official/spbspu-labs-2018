#include <iostream>
#include "base-types.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

using namespace std;

void resultIs ( Shape &s){
  cout << "Area is " << s.getArea() << endl;

  rectangle_t r = s.getFrameRect();
  cout << "Frame rectangle:" << endl;
  cout << "  Width is " << r.width << endl;
  cout << "  Hight is " << r.height << endl;
  cout << "  Center is in (" << r.pos.x << ", " << r.pos.y << ')' << endl;
}

int main()
{
  Rectangle rect(3.5, 4.8, {4.3, 3.4});
  rect.printRect();
  resultIs(rect);

  cout << "Rectangle to point (25,10)" << endl;
  rect.move({25,10});
  rect.printRect();

  cout << "dx = 15 dy = 5" << endl;
  rect.move(15,5);
  rect.printRect();

  cout << endl;

  Circle circ({5.9, 7.1}, 3.0);
  circ.printCircle();
  resultIs(circ);

  cout << "Circle to point (20,10)" << endl;
  circ.move({20,10});
  circ.printCircle();

  cout << "dx = 10 dy = 5" << endl;
  circ.move(10,5);
  circ.printCircle();


  return 0;

}

