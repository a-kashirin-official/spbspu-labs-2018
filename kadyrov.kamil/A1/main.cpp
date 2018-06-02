#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

void test(Shape &thisObject)
{
  std::cout << "Area is " << thisObject.getArea() << std::endl;
  thisObject.getFrameRect();
  std::cout << "Frame rectangle is obtained." << std::endl;
  thisObject.move(300, 300);
  std::cout << "Coordinate X of center is moved with dx = 300." << std::endl;
  std::cout << "Coordinate Y of center is moved with dy = 300." << std::endl;
  point_t updCenter = { 250 , 250 };
  thisObject.move(updCenter);
  std::cout << "After the second moving coordinates of center are (250,250)." << std::endl;
}
int main()
{
  point_t center = { 150 , 150 };
  rectangle_t rect = { 1000 , 2000 , center };
  Rectangle rectangle(rect);
  Circle circle(center, 10);
  std::cout << "Data of rectangle : " << std::endl;
  test(rectangle);
  std::cout << "Data of circle : " << std::endl;
  test(circle);
  return 0;
}
