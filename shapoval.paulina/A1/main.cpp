#include <iostream>

#include "circle.hpp"
#include "rectangle.hpp"

void printFrameRect(const Shape & object)
{
  const rectangle_t frame = object.getFrameRect();
  std::cout << "Centre: " << frame.pos.x << ", " << frame.pos.y << std::endl;
  std::cout << "Height: " << frame.height << std::endl;
  std::cout << "Width: " << frame.width << std::endl;
}

void printArea(const Shape & object)
{
  std::cout << "Area: " << object.getArea() << std::endl;
}

int main()
{
  Circle new_circle({0,0}, 10);

  std::cout << "CIRCLE  " << std::endl;
  printArea(new_circle);
  std::cout << "Start circleFrameRect parameters: " << std::endl;
  printFrameRect(new_circle);
  new_circle.move(10, 20);
  std::cout << "Move to x, y: " << std::endl;
  printFrameRect(new_circle);
  new_circle.move({20, 10});
  std::cout << "Move to point: " << std::endl;
  printFrameRect(new_circle);

  Rectangle new_rectangle({0,0}, 10, 20);

  std::cout << "RECTANGLE  " << std::endl;
  printArea(new_rectangle);
  std::cout << "Start circle parameters: " << std::endl;
  printFrameRect(new_rectangle);
  new_rectangle.move(10, 20);
  std::cout << "Move to x, y: " << std::endl;
  printFrameRect(new_rectangle);
  new_rectangle.move({20, 10});
  std::cout << "Move to point: " << std::endl;
  printFrameRect(new_rectangle);

  return 0;
}
