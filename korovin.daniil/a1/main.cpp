#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

void PrintParametrs( Shape & object)
{
  std::cout << "Width:" << object.getFrameRect().width << std::endl;
  std::cout << "Height:" << object.getFrameRect().height << std::endl;
  std::cout << "Area:" << object.getArea() << std::endl;
  std::cout << "pos(x):" << object.getFrameRect().pos.x << std::endl;
  std::cout << "pos(y):" << object.getFrameRect().pos.y << std::endl;
}

int main()
{
  Rectangle rectangle( {6.0, 3.0}, 2.0, 4.0 );
  std::cout << "Rectangle: \n";
  PrintParametrs(rectangle);
  std::cout << "After move to the specific point \n";
  rectangle.move( {14.0, 28.0} );
  PrintParametrs(rectangle);
  std::cout << "After move by adding coordinates \n";
  rectangle.move( 15.1, 38.22 );
  PrintParametrs(rectangle);

  Circle circle( {22.8, 32.2}, 10.0);
  std::cout << "Circle: \n";
  PrintParametrs(circle);
  std::cout << "After move to the specific point \n";
  rectangle.move( {82.0, 64.0} );
  PrintParametrs(circle);
  std::cout << "After move by adding coordinates \n";
  rectangle.move( 13.47, 123.4 );
  PrintParametrs(circle);

  return 0;
}
