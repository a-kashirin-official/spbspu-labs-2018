#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

using namespace std;

int main()
{
  Rectangle rect({8, 5, {-1, 7}});
  Shape *ptr = &rect;
  cout << "---Rectangle---" << endl;
  cout << "getArea result : " << ptr->getArea() << endl;
  cout << "getFrameRect result :" << endl
       << "center (" << ptr->getFrameRect().pos.x << ", " << ptr->getFrameRect().pos.y << ")" << endl
       << "width = " << ptr->getFrameRect().width << ", height = " << ptr->getFrameRect().height << endl;
  ptr->move(-4, 10);
  cout << "moving on dx = -4, dy = 10 result :" << endl
       << "new center is (" << ptr->getFrameRect().pos.x << ", " << ptr->getFrameRect().pos.y << ")" << endl;
  ptr->move({1, 1});
  cout << "moving to (1, 1) result :" << endl
       << "new center is (" << ptr->getFrameRect().pos.x << ", " << ptr->getFrameRect().pos.y << ")" << endl
       << "----------" << endl;
  Circle circ({9, {0, 8}});
  ptr = &circ;
  cout << "---Circle---" << endl;
  cout << "getArea result : " << ptr->getArea() << endl;
  cout << "getFrameRect result :" << endl
  << "center (" << ptr->getFrameRect().pos.x << ", " << ptr->getFrameRect().pos.y << ")" << endl
  << "width = " << ptr->getFrameRect().width << ", height = " << ptr->getFrameRect().height << endl;
  ptr->move(4.12, 2);
  cout << "moving on dx = 4.12, dy = 2 result :" << endl
       << "new center is (" << ptr->getFrameRect().pos.x << ", " << ptr->getFrameRect().pos.y << ")" << endl;
  ptr->move({5, 0});
  cout << "moving to (5, 0) result :" << endl
       << "new center is (" << ptr->getFrameRect().pos.x << ", " << ptr->getFrameRect().pos.y << ")" << endl;
  cout << "----------" << endl;
  return 0;
}
