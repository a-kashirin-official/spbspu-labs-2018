#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

void printParametrs( grigorev::Shape & object)
{
  std::cout << "pos(x):" << object.getFrameRect().pos.x << "; " << "pos(y):" << object.getFrameRect().pos.y << std::endl;
  std::cout << "width:" << object.getFrameRect().width << "; " << "height:" << object.getFrameRect().height << std::endl;
  std::cout << "Area:" << object.getArea() << std::endl;
}

int main()
{
  const grigorev::point_t DOT={3.5, 5.6};
  grigorev::Rectangle rectangle( {3.0, 4.0}, 10.0, 5.0 );
  std::cout << "Rectangle:" << std::endl;
  printParametrs(rectangle);
  std::cout << "\n"<< std::endl;
  std::cout << "After move(To dot)" << std::endl;
  rectangle.move(DOT);
  printParametrs(rectangle);
  std::cout << "\n"<< std::endl;
  std::cout << "After move(dx,dy)" << std::endl;
  rectangle.move( 3.46, 6.57 );
  printParametrs(rectangle);
  std::cout << "\n"<< std::endl;
  std::cout << "After scale" << std::endl;
  rectangle.scale(5.0);
  printParametrs(rectangle);

  grigorev::Circle circle( {4.0, 5.3}, 10.01);
  std::cout << "\n"<< std::endl;
  std::cout << "Circle:" << std::endl;
  printParametrs(circle);
  std::cout << "\n"<< std::endl;
  std::cout << "After move(To dot)" << std::endl;
  circle.move(DOT);
  printParametrs(circle);
  std::cout << "\n"<< std::endl;
  std::cout << "After move(dx,dy)" << std::endl;
  circle.move( 13.36, 7.33 );
  printParametrs(circle);
  std::cout << "\n"<< std::endl;
  std::cout << "After scale" << std::endl;
  circle.scale(3.0);
  printParametrs(circle);

  return 0;
}
