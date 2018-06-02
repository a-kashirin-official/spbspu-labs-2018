#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

using namespace mihajlov;

void moveObject(Shape & obj, const point_t & centerPos)
{
  std::cout << "Old data_: " << std::endl;
  obj.getInfo();
  obj.move(centerPos);
  std::cout << std::endl << "New data_: " << std::endl;
  obj.getInfo();
  std::cout << "Area of Shape: " << obj.getArea() << ";" << std::endl << std::endl;
}
void moveObject(Shape & obj, const double shiftX, const double shiftY)
{
  std::cout << "Old data_: " << std::endl;
  obj.getInfo();
  std::cout << std::endl << "New data_: " << std::endl;
  obj.move(shiftX, shiftY);
  obj.getInfo();
  std::cout << "Area of Shape: " << obj.getArea() << ";" << std::endl << std::endl;
}

void scaleObject(Shape & obj, const double & multiplier)
{
  std::cout << "Area before: " << obj.getArea() << std::endl;
  obj.scale(multiplier);
  std::cout << "Area after: " << obj.getArea() << std::endl;
}
int main()
{
  try
  {
    Rectangle rectangle({100.0, 200.0}, 10.0, 20.0);
    Circle circle({200.0, 100.0}, 50.0);
    Rectangle frame(circle.getFrameRect().pos, circle.getFrameRect().height,circle.getFrameRect().height);
    moveObject(rectangle, {25.0, 55.0});
    moveObject(circle, 267.0, 333.0);
    frame.getInfo();
    scaleObject(frame, 3.0);
  }
  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}
