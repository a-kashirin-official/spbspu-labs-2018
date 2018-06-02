#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

using namespace std;
using namespace subtselnaya;

void printResults(const Shape & s)
{
  cout << "  Area is " << s.getArea() << endl;
  rectangle_t r = s.getFrameRect();
  cout << "  Frame rectangle has width - " << r.width << ", height - " << r.height << endl;
  cout << "    Center is in (" << r.pos.x << ", " << r.pos.y << ')' << endl;
}

void printResults1(const CompositeShape & s)
{
  cout <<"  CompositeShape.size = "<< s.size() << endl;
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

  cout << endl;

  cout << "Creating CompositeShape" << endl;
  
  rect = {1.0, 1.0, {0.0, 0.0}};
  circ = {{3.0, 3.0}, 1.0};

  CompositeShape composhape;
  CompositeShape::ptr_type rectPtr = make_shared < Rectangle > (rect);
  CompositeShape::ptr_type circPtr = make_shared < Circle > (circ);

  cout << "Adding rectangle" << endl;
  composhape.addShape(rectPtr);
  printResults1(composhape);

  cout << "Adding circle" << endl;
  composhape.addShape(circPtr);
  printResults1(composhape);

  cout << "Scaling CompositeShapee with 2.0" << endl;
  composhape.scale(2.0);
  cout << "New parameters of CompositeShape:" << endl;
  printResults1(composhape);


  std::cout << "Moving CompositeShape to point (-3.0 , -3.0)" << endl;
  composhape.move({-3.0, -3.0});
  printResults1(composhape);

  cout << "Moving CompositeShape with dx = 3.0 dy = 3.0" << endl;
  composhape.move(3.0, 3.0);
  printResults1(composhape);

  cout << "Removing first shape" << endl;
  composhape.removeShape(1);
  printResults1(composhape);

  return 0;
}
