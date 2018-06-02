#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

void printInfo(almukhametov::Shape & shape)
{
  std::cout << "  Width: " << shape.getFrameRect().width << std::endl;
  std::cout << "  Height: " << shape.getFrameRect().height << std::endl;
  std::cout << "  Area: " << shape.getArea() << std::endl;
  std::cout << "  Position (x, y): (" << shape.getFrameRect().pos.x
            << ", "<< shape.getFrameRect().pos.y << ")" << std::endl;
}

int main()
{
  try
  {
    almukhametov::Rectangle rectangle(4.0, 5.0, {0.0, 0.0});
    std::cout << "Rectangle:" << std::endl;
    printInfo(rectangle);
    rectangle.move({2.0, 8.0});
    rectangle.move(5.0, 6.0);
    std::cout << "Rectangle after movement:" << std::endl;
    printInfo(rectangle);
    rectangle.scale(3.5);
    std::cout << "Rectangle after scaling: " << std::endl;
    printInfo(rectangle);

    std::cout << std::endl;

    almukhametov::Circle circle(1.0, {10.0, 15.0});
    std::cout << "Circle: " << std::endl;
    printInfo(circle);
    circle.move({5.0, 8.0});
    circle.move(1.0, 3.0);
    std::cout << "Circle after movement: " << std::endl;
    printInfo(circle);
    circle.scale(2.0);
    std::cout << "Circle after scaling: " << std::endl;
    printInfo(circle);
  }
  catch(const std::exception& e)
  {
    std::cout << e.what();
    return 1;
  }

  return 0;
}
