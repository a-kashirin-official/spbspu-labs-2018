#include "circle.hpp"
#include "rectangle.hpp"
#include <iostream>

void printFrameRect( Shape & shape )
{
  rectangle_t frameRect = shape.getFrameRect();
  std::cout << "Framed rectangle:" << std::endl;
  std::cout << "Height is :" << frameRect.height << std::endl;
  std::cout << "Width is:" << frameRect.width << std::endl;
  std::cout << "Center is:" << std::endl;
  std::cout << frameRect.pos.x << "," << frameRect.pos.y << std::endl;
}
int main()
{
  point_t rec_point = {19, 17};
  Rectangle rectangle(rec_point, 50, 70);
  std::cout << "Rectangle:" << std::endl;
  std::cout << "Coordinates of the center are:" << rec_point.x << "," << rec_point.y << std::endl;
  rectangle.move(10.0,16.0);
  std::cout << "New coordinates of the center are:" << rec_point.x << "," << rec_point.y << std::endl;
  point_t newpoint = {1.2, 7.8};
  rectangle.move(newpoint);
  std::cout << "New coordinates of the center are:" << rec_point.x << "," << rec_point.y << std::endl;
  std::cout << "Rectangle area is" << rectangle.getArea() << std:: endl;
  printFrameRect(rectangle);

  point_t cir_point = {10, 11};
  Circle circle(cir_point, 10);
  std::cout << "Circle:" << std::endl;
  std::cout << "Coordinates of the center are:" << cir_point.x << "," << cir_point.y << std::endl;
  circle.move(7.0, 13.0);
  std::cout << "New coordinates of the center are:" << cir_point.x << "," << cir_point.y << std::endl;
  circle.move(newpoint);
  std::cout << "New coordinates of the center are:" << cir_point.x << "," << cir_point.y << std::endl;
  std::cout << "Circle area is" << circle.getArea() << std:: endl;
  printFrameRect(circle);

 return 0;
}


