#include "rectangle.hpp"
#include "circle.hpp"
#include <iostream>

using namespace std;

void printInfo(const Shape & shape)
{
  cout << "getArea = " << shape.getArea() << endl;
  const rectangle_t temp = shape.getFrameRect();
  cout << "FrameRect:" << endl;
  cout << "Mid = (" << temp.pos.x << ", " << temp.pos.y << ")" << endl;
  cout << "Width = " << temp.width << " Height = " << temp.height << endl;
  cout << endl;
}

int main()
{
  const point_t point{ 71.3, 89.8 };
  Shape * circ1 = nullptr;
  Shape * rect1 = nullptr;
  
  try
  {
    rect1 = new Rectangle({ 15.5, 2.9, { 43.2, 27.1 } });
    circ1 = new Circle(12.4, point);
    cout << "Circle:" << endl;
    printInfo(*circ1);
    circ1->move(45.3, 35.1);
    printInfo(*circ1);
    delete circ1;
    cout << "Rectangle:" << endl;
    printInfo(*rect1);
    rect1->move(point);
    printInfo(*rect1);
    delete rect1;
  }
  catch(bad_alloc & b)
  {
    delete circ1;
    delete rect1;
    cerr << b.what() << endl;
    return 2;
  }
  catch (invalid_argument & i)
  {
    delete circ1;
    delete rect1;
    cerr << i.what() << endl;
    return 1;
  };
  return 0;
}
