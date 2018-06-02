#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
using namespace std;
void conclusion(Shape & currentObj){

  cout << "area is " << currentObj.getArea() << endl;
  cout << "w = " << currentObj.getFrameRect().width << ", h = " << currentObj.getFrameRect().height << endl;

  currentObj.move(3.3, 3.3);
  cout << "now pos is " << currentObj.getFrameRect().pos.x << "," << currentObj.getFrameRect().pos.y << endl;

  currentObj.move({3,3});
  cout << "now pos is " << currentObj.getFrameRect().pos.x << "," << currentObj.getFrameRect().pos.y << endl;
}
int main(){
  Rectangle exRec({5,5}, 2, 4);
  Circle exCircle({5,5}, 3);

  conclusion(exRec);
  conclusion(exCircle);
  return 0;
}

