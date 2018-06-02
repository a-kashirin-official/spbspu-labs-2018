#include <cstdlib>
#include <iostream>
#include "circle.hpp"
#include "base-types.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

using std::cout;
using std::endl;
using namespace neizhko;

void test(Shape& obj)
{
  obj.printInfo();
  point_t cc;
  cc.x = 250;
  cc.y = 250;
  obj.move(cc);
  obj.move(55, 55);
  obj.scale(2);
  obj.printInfo();
}

int main()
{
  try
  {
    Rectangle rec(14, 14, 15, 25);
    test(rec);
    Circle cir(14, 7, 3);
    test(cir);
    Triangle tri(5, 5, 5, 15, 15, 15);
    test(tri);
  }
  catch (const std::exception& e)
  {
    cout << e.what();
    return 1;
  }
  return 0;
}
