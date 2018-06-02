#include <iostream>
#include "../common/circle.hpp"
#include "../common/base-types.hpp"
#include "../common/composite-shape.hpp"
#include "../common/rectangle.hpp"
using std::cout;
using std::endl;
using namespace razuvaev;

int main() {
  try
  {
    Rectangle rec(3,3,10,15);
    Circle cir(10,7,3);
    CompositeShape shp(&rec);  
    shp.writeInfoOfObject();
    shp.addShape(&cir);
    shp.writeInfoOfObject();
    
    shp.writeInfoOfObject();
    point_t cc;
    cc.x = 150;
    cc.y = 100;
    shp.move(cc);
    shp.move(1,1);
    shp.scale(2);
    shp.writeInfoOfObject();
    
    shp.deleteShape(1);
    shp.writeInfoOfObject();   
  }
  
  catch (const std::exception& e){
    cout << e.what();
    return 1;
  }
  
  return 0; 
}
