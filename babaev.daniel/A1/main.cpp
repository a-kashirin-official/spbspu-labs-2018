#include <cstdlib>
#include <iostream>
#include "circle.hpp"
#include "base-types.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

using std::cout;
using std::endl;

void test(Shape& obj)
{
  obj.printInfo();
  point_t cc;
  cc.x = 350;
  cc.y = 100;
  obj.move(cc);
  obj.printInfo();
  obj.move(55, 55);
  obj.printInfo();
}

int main()
{
  try
  {
    Rectangle rec(20, 20, 35, 30);
    test(rec);
    Circle cir(14, 10, 40);
    test(cir);
    Triangle tri(5, 5, 5, 15, 10, 13);
    test(tri);
  }
  catch (const std::exception& e)
  {
    cout << e.what();
    return 1;
  }
  return 0;
}
