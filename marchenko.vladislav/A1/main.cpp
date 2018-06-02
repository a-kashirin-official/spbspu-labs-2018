#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

void testClasses(Shape &thisObject)
{
  std::cout << "Area of this figure is " << thisObject.getArea() << std::endl;
  std::cout << "Width of frame rectangle of this figure is " << thisObject.getFrameRect().width << std::endl;
  std::cout << "Height of frame rectangle of this figure is " << thisObject.getFrameRect().height << std::endl;
  std::cout << "Coordinate X of center of frame rectangle of this figure is " << thisObject.getFrameRect().pos.x << std::endl;
  std::cout << "Coordinate Y of center of frame rectangle of this figure is " << thisObject.getFrameRect().pos.y << std::endl;
  thisObject.move(100, 100);
  std::cout << "Coordinate X of center of this figure is moved with dx = 100." << std::endl;
  std::cout << "Coordinate Y of center of this figure is moved with dy = 100." << std::endl;
  point_t newCenter = { 200 , 200 };
  thisObject.move(newCenter);
  std::cout << "Updated coordinates of center of this figure are (200,200)." << std::endl;
}
int main()
{
  point_t center = { 50 , 50 };
  Rectangle rect(100, 200, center);
  Circle circle(center, 10);
  std::cout << "Testing methods of rectangle : " << std::endl;
  testClasses(rect);
  std::cout << "Testing methods of circle : " << std::endl;
  testClasses(circle);
  return 0;
}
