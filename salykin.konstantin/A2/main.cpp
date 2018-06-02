#include <iostream>

#include "circle.hpp"
#include "rectangle.hpp"

using namespace salykin;
using std::cout;
using std::endl;
using std::cerr;
using std::invalid_argument;

int main()
{
  double mult = 0;

  try{
    Circle crcl(3.33, {17.6, 10.2});
    cout << "Area of circle before scaling: " << crcl.getArea() << endl;
    mult = 0.4;
    crcl.scale(mult);
    cout << "Area of circle after scaling: " << crcl.getArea() << endl
         << "Multiplier: " << mult << endl;

    Rectangle rctngl(8.25, 3.14, {25.0, 25.0});
    cout << "Area of rectangle before scaling: " << rctngl.getArea() << endl;
    mult = 2.16;
    rctngl.scale(mult);
    cout << "Area of rectangle after scaling: " << rctngl.getArea() << endl
         << "Multiplier: " << mult << endl;
  } catch(invalid_argument & ia) {
    cerr << ia.what() << endl;
    return 1;
  }
  return 0;
}
