#include <iostream>
#include "circle.hpp"
#include "base-types.hpp"
#include "composite-shape.hpp"
#include "rectangle.hpp"
using std::cout;
using std::endl;
using namespace averin;

void test(Shape& obj)
{
  obj.printInfo();
  point_t cc;
  cc.x = 150;
  cc.y = 100;
  obj.move(cc);
  obj.move(1,1);
  obj.scale(2);
  obj.printInfo();
}

int main() 
{
  try
  {
    Rectangle rec(3,3,10,15);
    Circle cir(10,7,3);
    CompositeShape shp(&rec);  
    shp.printInfo();
    shp.addShape(&cir);
    shp.printInfo();
    test(shp);
    shp.deleteShape(1);
    shp.printInfo(); 
  }
  
  catch (const std::exception& e)
  {
    cout << e.what();
    return 1;
  }
  return 0; 
}
