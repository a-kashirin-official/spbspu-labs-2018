#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

void PrintParametrs( Shape & object)
{
  std::cout << "width:" << object.getFrameRect().width << std::endl;
  std::cout << "height:" << object.getFrameRect().height << std::endl;
  std::cout << "Area:" << object.getArea() << std::endl;
  std::cout << "pos(x):" << object.getFrameRect().pos.x << std::endl;
  std::cout << "pos(y):" << object.getFrameRect().pos.y << std::endl;
}

int main()
{
  Rectangle rectangle( {3.0, 4.0}, 10.0, 5.0 );
  std::cout << "Rectangle:" << std::endl;
  PrintParametrs(rectangle);
  std::cout << "After move(point)" << std::endl;
  rectangle.move( {2.55, 3.44} );
  PrintParametrs(rectangle);
  std::cout << "After move(dx,dy)" << std::endl;
  rectangle.move( 3.46, 6.57 );
  PrintParametrs(rectangle);

  Circle circle( {4.0, 5.3}, 10.01);
  std::cout << "Circle:" << std::endl;
  PrintParametrs(circle);
  std::cout << "After move(point)" << std::endl;
  circle.move( {11.01, 4.37} );
  PrintParametrs(circle);
  std::cout << "After move(dx,dy)" << std::endl;
  circle.move( 13.36, 7.33 );
  PrintParametrs(circle);

  return 0;
}
