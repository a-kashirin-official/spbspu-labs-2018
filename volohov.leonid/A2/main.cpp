#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
using namespace volohov;

void PrintInfo(Shape & object)
{
  std::cout << "Width:" << object.getFrameRect().width << std::endl;
  std::cout << "Height:" << object.getFrameRect().height << std::endl;
  std::cout << "pos(x):" << object.getFrameRect().pos.x << std::endl;
  std::cout << "pos(y):" << object.getFrameRect().pos.y << std::endl;
  std::cout << "Area:" << object.getArea() << std::endl;
}

int main()
{
  //example of Rectangle work
  Rectangle rectangle( {1.1, 2.2}, 3.3, 4.4 );
  std::cout << "Rectangle info:" << std::endl;
  PrintInfo(rectangle);

  rectangle.move( {20.0, 20.0} );
  std::cout << "Rectangle after move(point)" << std::endl;
  PrintInfo(rectangle);

  rectangle.move( 10.0, 10.0 );
  std::cout << "Rectangle after move(dx, dy)" << std::endl;
  PrintInfo(rectangle);

  rectangle.scale(2.0);
  PrintInfo(rectangle);

  //example of Circle work
  Circle circle( {1.0, 2.0}, 3.0);
  std::cout << "Circle info:" << std::endl;
  PrintInfo(circle);

  circle.move( {20.0, 20.0} );
  std::cout << "Circe after move(point)" << std::endl;
  PrintInfo(circle);

  circle.move( 30.0, 30.0 );
  std::cout << "Circle after move(dx, dy)" << std::endl;
  PrintInfo(circle);

  circle.scale(2.0);
  PrintInfo(circle);

  return 0;
}
