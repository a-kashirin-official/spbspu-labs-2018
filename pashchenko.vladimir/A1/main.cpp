#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

int main()
{
  point_t pointDefOne = {45.6, 13.0};
  point_t pointDefThree = {10.5, -3.0};

  point_t pointTo = { 3, 13.0 };

  Rectangle rect(pointDefOne, 20, 5.5);
  Triangle triangle({ 1, 2 }, { 7.5, 6 }, { 10.5, 5 });
  Circle circle(pointDefThree, 4.5);

  std::cout << "Rectangle: " << std::endl;

  std::cout << "Coordinates: X: " << rect.getFrameRect().pos.x << " Y: " << rect.getFrameRect().pos.y << std::endl;
  std::cout << "Width: " << rect.getFrameRect().width << " Height: " << rect.getFrameRect().height << std::endl;
  std::cout << "Area: " << rect.getArea() << std::endl;

  std::cout << "Triangle: " << std::endl;

  std::cout << "Before changing position:" << std::endl;
  std::cout << "Coordinates: X: " << triangle.getFrameRect().pos.x << " Y: " << triangle.getFrameRect().pos.y << std::endl;
  std::cout << "Width: " << triangle.getFrameRect().width << " Height: " << triangle.getFrameRect().height << std::endl;
  std::cout << "Area: " << triangle.getArea() << std::endl;

  std::cout << "New position: X: " << pointTo.x << " Y: " << pointTo.y << std::endl;
  triangle.move(pointTo);

  std::cout << "Coordinates: X: " << triangle.getFrameRect().pos.x << " Y: " << triangle.getFrameRect().pos.y << std::endl;
  std::cout << "Width: " << triangle.getFrameRect().width << " Height: " << triangle.getFrameRect().height << std::endl;
  std::cout << "Area: " << triangle.getArea() << std::endl;

  std::cout << "Circle: " << std::endl;
  std::cout << "Coordinates: X: " << circle.getFrameRect().pos.x << " Y: " << circle.getFrameRect().pos.y << std::endl;
  std::cout << "Width: " << circle.getFrameRect().width << " Height: " << triangle.getFrameRect().height << std::endl;
  std::cout << "Area: " << circle.getArea() << std::endl;

  circle.move(-1.4, 3.5);
  std::cout << "After moving: " << std::endl;
  std::cout << "Coordinates: X: " << circle.getFrameRect().pos.x << " Y: " << circle.getFrameRect().pos.y << std::endl;
  std::cout << "Width: " << circle.getFrameRect().width << " Height: " << triangle.getFrameRect().height << std::endl;
  std::cout << "Area: " << circle.getArea() << std::endl;

  return 0;
}
