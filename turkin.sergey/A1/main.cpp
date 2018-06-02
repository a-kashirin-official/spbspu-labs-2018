#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

void OutMat(Shape &o);

void OutMat(Shape &o)
{
  std::cout << "Width:" << o.getFrameRect().width << std::endl;
  std::cout << "Height:" << o.getFrameRect().height << std::endl;
  std::cout << "Area:" << o.getArea() << std::endl;
  std::cout << "Pos(x):" << o.getFrameRect().pos.x << std::endl;
  std::cout << "Pos(y):" << o.getFrameRect().pos.y << std::endl;
  std::cout << "_________________" << std::endl;
}

int main()
{
  Rectangle rectangle(7.0, 2.0, {1.0, 2.0});
  rectangle.printInfo();
  OutMat(rectangle);
  std::cout << "After move(point)" << std::endl;
  rectangle.move({3.05, 7.49});
  OutMat(rectangle);
  std::cout << "After move(dx,dy)" << std::endl;
  rectangle.move(5.09, 7.57);
  OutMat(rectangle);

  Circle circle(7.15, {2.0, 7.5});
  std::cout << "- - - - - - - - - - - - - - " << std::endl;
  circle.printInfo();
  OutMat(circle);
  std::cout << "After move(point)" << std::endl;
  circle.move({9.51, 3.9});
  OutMat(circle);
  std::cout << "After move(dx,dy)" << std::endl;
  circle.move(10.23, 6.07);
  OutMat(circle);

  Triangle triangle({3.5, 6.0}, {9.7, 6.5}, {2.3, 4.5});
  std::cout << "- - - - - - - - - - - - - - " << std::endl;
  triangle.printInfo();
  OutMat(triangle);
  std::cout << "After move(point)" << std::endl;
  triangle.move({6.55, 9.49});
  triangle.printInfo();
  OutMat(triangle);
  std::cout << "After move(dx,dy)" << std::endl;
  triangle.move(6.09, 6.57);
  triangle.printInfo();
  OutMat(triangle);
  return 0;
}
