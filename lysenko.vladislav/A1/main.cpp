#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

void PrintParametrs( Shape & object)
{
  std::cout << "Width:" << object.getFrameRect().width << std::endl;
  std::cout << "Height:" << object.getFrameRect().height << std::endl;
  std::cout << "Area:" << object.getArea() << std::endl;
  std::cout << "Pos(x):" << object.getFrameRect().pos.x << std::endl;
  std::cout << "Pos(y):" << object.getFrameRect().pos.y << std::endl;
}

void Demonstration(Shape & shape, const char Figure[])
{
  std::cout << Figure << std::endl;
  PrintParametrs(shape);
  std::cout << "After move(to a specific point):" << std::endl;
  shape.move( {6.0, 6.0} );
  PrintParametrs(shape);
  std::cout << "After move(dx,dy):" << std::endl;
  shape.move( 6.0, 6.0 );
  PrintParametrs(shape);
}
int main()
{
  Rectangle rectangle( {10.0, 10.0}, 32.0, 32.0 );
  Demonstration(rectangle,"Rectangle:");

  Circle circle( {32.0, 32.0}, 12.0);
  Demonstration(circle,"Circle:");

  return 0;
}
