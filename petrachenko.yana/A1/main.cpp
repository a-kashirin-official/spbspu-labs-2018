#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

void showInf(const Shape &shape)
{
  std::cout << "Width of the frame is " << shape.getFrameRect().width << std::endl;
  std::cout << "Height of the frame is " << shape.getFrameRect().height << std::endl;
  std::cout << "Center of the frame is (" << shape.getFrameRect().pos.x
  << "," << shape.getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Area of the shape is " << shape.getArea() << std::endl;
  std::cout << std::endl;
}

int main()
{
  Rectangle rectangle(200.5, 300.0, {15.0, 9.0});
  Circle circle(30.0, {20.0, 25.6});

  std::cout << "For rectangle : " << std::endl;
  showInf(rectangle);
  std::cout << "For circle : " << std::endl;
  showInf(circle);

  std::cout << "Move rectangle to (50.0, 50.0) " << std::endl;
  rectangle.move({50.0, 50.0});
  showInf(rectangle);
  std::cout << "Move circle to (75.3, 70) " << std::endl;
  circle.move({75.3, 70.0});
  showInf(circle);

  std::cout << "Move rectangle to (x+100, y+0.8) " << std::endl;
  rectangle.move(100.0, 0.8);
  showInf(rectangle);
  std::cout << "Move circle to (x+30.5, y+10) " << std::endl;
  circle.move(30.5, 10.0);
  showInf(circle);

  return 0;
}

