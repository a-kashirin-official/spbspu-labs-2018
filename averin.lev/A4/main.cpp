#include <iostream>
#include "circle.hpp"
#include "base-types.hpp"
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "matrix.hpp"
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
    std::shared_ptr<Rectangle> rec = std::make_shared<Rectangle>(1,1,0,0);
    std::shared_ptr<Rectangle> rec2 = std::make_shared<Rectangle>(2,2,0,0);
    std::shared_ptr<Rectangle> rec3 = std::make_shared<Rectangle>(4,4,0,0);
    std::shared_ptr<Rectangle> rec4 = std::make_shared<Rectangle>(6,6,0,0);
    Rectangle rec5(15,10,1,7);
    std::shared_ptr<CompositeShape> shp = std::make_shared<CompositeShape>(&rec5);  
    Circle cir1(3,5,9);
    shp->addShape(&cir1);
    shp->rotate(90);
    shp->printInfo();
    std::shared_ptr<Circle> cir2 = std::make_shared<Circle>(1,1000,1000);
    std::shared_ptr<Circle> cir3 = std::make_shared<Circle>(10,-1000,1);
    Matrix matrix;
    matrix.addShape(rec);
    matrix.addShape(cir3);
    matrix.addShape(rec2);
    matrix.addShape(rec3);
    matrix.addShape(rec4);  
    matrix.addShape(cir2);
    matrix.addShape(shp);
    matrix.printInfo();
  }
  
  catch (const std::exception& e)
  {
    cout << e.what();
    return 1;
  }
  return 0; 
}
