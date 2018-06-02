#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

void print(const Shape & figure)
{
  std::cout << "Area " << figure.getArea() << std::endl;
  std::cout << "Coordinates (x, y): ";
  std::cout << figure.getFrameRect().pos.x << ";" << figure.getFrameRect().pos.y << std::endl;
  std::cout << "Height - " << figure.getFrameRect().height << std::endl;
  std::cout << "Width - " << figure.getFrameRect().width << std::endl;
}

int main()
{
  point_t RectCenter = {50, 20};
  Rectangle r({RectCenter, 30, 40});

  std::cout << "Rectangle: " << std::endl;
  print(r);

  r.move({10, -10});
  std::cout << "-----After moving-----" << std::endl;
  print(r);

  point_t CircCenter = {30, 5};
  Circle c(CircCenter, 20);

  std::cout << std::endl;
  std::cout << "Circle: " << std::endl;
  print(c);

  c.move(10, -10);
  std::cout << "-----After moving-----" << std::endl;
  print(c);

  return 0;
}
