#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

using std::cout;
using std::cerr;
using std::endl;

void ShapeInfo(const Shape & shape)
{
  cout << "Area = " << shape.getArea() << endl;
  rectangle_t rectan = shape.getFrameRect();
  cout << "Frame rectangle:" << endl;
  cout << "x = " << rectan.pos.x << endl;
  cout << "y = " << rectan.pos.y << endl;
  cout << "width = " << rectan.width << endl;
  cout << "height = " << rectan.height << endl << endl;
}

int main()
{
  Rectangle rectangle{ { {25.0, 25.0}, 5.0, 10.0 } };
  Circle circle{ {50.0, 50.0}, 10.0 };

  cout << "Rectangle" << endl;
  ShapeInfo(rectangle);

  cout << "Circle" << endl;
  ShapeInfo(circle);

  rectangle.move({ 0.0, 0.0 });
  circle.move({ 0.0, 0.0 });

  cout << "Rectangle" << endl;
  ShapeInfo(rectangle);

  cout << "Circle" << endl;
  ShapeInfo(circle);

  rectangle.move( 10.0, 10.0 );
  rectangle.move( -10.0, -10.0 );

  cout << "Rectangle" << endl;
  ShapeInfo(rectangle);

  cout << "Circle" << endl;
  ShapeInfo(circle);
  return 0;
}
