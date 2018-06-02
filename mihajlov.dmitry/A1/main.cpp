#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

void moveObject(Shape & obj, const point_t & centerPos)
{
  std::cout << "Old data: " << std::endl;
  obj.getInfo();
  obj.move(centerPos);
  std::cout << std::endl << "New data: " << std::endl;
  obj.getInfo();
  std::cout << "Area of Shape: " << obj.getArea() << ";" << std::endl << std::endl;
}
void moveObject(Shape & obj, const double shiftX, const double shiftY)
{
  std::cout << "Old data: " << std::endl;
  obj.getInfo();
  std::cout << std::endl << "New data: " << std::endl;
  obj.move(shiftX, shiftY);
  obj.getInfo();
  std::cout << "Area of Shape: " << obj.getArea() << ";" << std::endl << std::endl;
}
int main()
{
  try
  {
    Rectangle rectangle({100, 200}, 10, 20);
    Circle circle({200, 100}, 50);
    Rectangle frame(circle.getFrameRect());
    moveObject(rectangle, {25, 55});
    moveObject(circle, 267, 333);
    frame.getInfo();
  }
  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}
