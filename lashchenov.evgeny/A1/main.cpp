#include "circle.hpp"
#include "rectangle.hpp"
#include <iostream>

void printInfoAboutShape(const Shape & shape)
{
  shape.printInfo();
}

int main()
{
  Circle circle(5, {1, 0});
  Rectangle rectangle(5, 6, 1, 0);

  printInfoAboutShape(circle);
  printInfoAboutShape(rectangle);

  circle.move({1, 2});
  printInfoAboutShape(circle);

  std::cout << "Area is " << circle.getArea() << std::endl;

  return 0;
}
