#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

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
  Rectangle Rectangle( {1.1, 2.2}, 3.3, 4.4 );
  std::cout << "Rectangle info:" << std::endl;
  PrintInfo(Rectangle);

  Rectangle.move( {20.0, 20.0} );
  std::cout << "Rectangle after move(point)" << std::endl;
  PrintInfo(Rectangle);

  Rectangle.move( 10.0, 10.0 );
  std::cout << "Rectangle after move(dx, dy)" << std::endl;
  PrintInfo(Rectangle);

  //example of Circle work
  Circle Circle( {1.0, 2.0}, 3.0);
  std::cout << "Circle info:" << std::endl;
  PrintInfo(Circle);

  Circle.move( {20.0, 20.0} );
  std::cout << "Circe after move(point)" << std::endl;
  PrintInfo(Circle);

  Circle.move( 30.0, 30.0 );
  std::cout << "Circle after move(dx, dy)" << std::endl;
  PrintInfo(Circle);

  return 0;
}
