#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

using namespace std;
using namespace orlov;


int main()
{
  Rectangle rect({10, 10, { 5, 5 }});
  cout << "Rectangle\n" << "\tArea before scale = " << rect.getArea() << endl;
  rect.scale(2);
  cout << "\tk = 2, Area after scale = " << rect.getArea() << endl;

  Circle circ(5, { 10, 10 });
  cout << "Circle\n" << "\tArea before scale = " << circ.getArea() << endl;
  circ.scale(2);
  cout << "\tk = 2, Area after scale = " << circ.getArea() << endl;

  Triangle trng({ 10.6, 13.2 }, { 15.2, 18.0 }, { 11.1, 15.6 });
  cout << "Triangle\n" << "\tArea  before scale = " << trng.getArea() << endl;
  trng.scale(10);
  cout << "\tk = 10, Area after scale = " << trng.getArea() << endl;

return 0;
}
