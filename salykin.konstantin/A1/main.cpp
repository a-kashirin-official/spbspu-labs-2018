#include <iostream>

#include "circle.hpp"
#include "rectangle.hpp"

using std::cout;
using std::endl;
using std::cerr;
using std::invalid_argument;

void printShapeInfo(const Shape& shape)
{
  cout << "Area = " << shape.getArea() << endl;
  const rectangle_t frame = shape.getFrameRect();
  cout << "FrameRectangle: " << endl;
  cout << "Center: (" << frame.pos.x << ", " << frame.pos.y << ")" << endl;
  cout << "Width = " << frame.width << endl;
  cout << "Height = " << frame.height << endl << endl;
}

int main()
{
  try
  {
    Circle crcl(3.33, {17.6, 10.2});
    cout << endl << "Circle info:" << endl;
    printShapeInfo(crcl);
    cout << "After first move:" << endl;
    crcl.move(5.0, 5.0);
    printShapeInfo(crcl);
    cout << "After second move:" << endl;
    crcl.move({5.0, 5.0});
    printShapeInfo(crcl);

    Rectangle rcrtgl(8.25, 3.14, {25.0, 25.0});
    cout << endl << "Rectangle info:" << endl;
    printShapeInfo(rcrtgl);
    cout << "After first move:" << endl;
    rcrtgl.move(16.4, 17.5);
    printShapeInfo(rcrtgl);
    cout << "After second move:" << endl;
    rcrtgl.move({16.4, 17.5});
    printShapeInfo(rcrtgl);
  } catch(invalid_argument& ia) {
    cerr << ia.what() << endl;
    return 1;
  }
  return 0;
}
