#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
using namespace gessen;

void PrintParametrs(Shape & object)
{
  std::cout << "width:" << object.getFrameRect().width << std::endl;
  std::cout << "height:" << object.getFrameRect().height << std::endl;
  std::cout << "Area:" << object.getArea() << std::endl;
  std::cout << "pos(x):" << object.getFrameRect().pos.x << std::endl;
  std::cout << "pos(y):" << object.getFrameRect().pos.y << std::endl;
}

int main()
{
  Rectangle rectangle( {8.0, 9.0}, 10.0, 6.0 );
  std::cout << "Rectangle:" << std::endl;
  PrintParametrs(rectangle);
  std::cout << "After move(point)" << std::endl;
  rectangle.move( {14.0, 28.0} );
  PrintParametrs(rectangle);
  std::cout << "After move(dx,dy)" << std::endl;
  rectangle.move( 15.1, 38.22 );
  PrintParametrs(rectangle);
  rectangle.scale(2.0);
  PrintParametrs(rectangle);

  Circle circle( {22.8, 32.2}, 10.0);
  std::cout << "Circle:" << std::endl;
  PrintParametrs(circle);
  std::cout << "After move(point)" << std::endl;
  circle.move( {82.0, 64.0} );
  PrintParametrs(circle);
  std::cout << "After move(dx,dy)" << std::endl;
  circle.move( 13.47, 123.4 );
  PrintParametrs(circle);
  circle.scale(2.0);
  PrintParametrs(circle);

  return 0;
}
