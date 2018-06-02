#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

void OutDataShape(const Shape &shape) {
  shape.OutData();
}

int main() {

  Rectangle rectangle(5.2, 2.6, {3.2, 1.3});
  std::cout << "\nRectangle : " << std::endl;
  OutDataShape(rectangle);
  std::cout << "S(rectangle) = " << rectangle.getArea() << std::endl;
  std::cout << "Spot of middle on Ox = " << rectangle.getFrameRect().pos.x << std::endl;
  std::cout << "Spot of middle on Oy = " << rectangle.getFrameRect().pos.y << std::endl << std::endl;
  std::cout << "After moving" << std::endl;
  rectangle.move({3.3, 2.3});
  std::cout << "S(rectangle) = " << rectangle.getArea() << std::endl;
  std::cout << "Spot of middle on Ox = " << rectangle.getFrameRect().pos.x << std::endl;
  std::cout << "Spot of middle on Oy = " << rectangle.getFrameRect().pos.y << std::endl << std::endl;
  std::cout << "After moving" << std::endl;
  rectangle.move(10, 10);
  std::cout << "S(rectangle) = " << rectangle.getArea() << std::endl;
  std::cout << "Spot of middle on Ox = " << rectangle.getFrameRect().pos.x << std::endl;
  std::cout << "Spot of middle on Oy = " << rectangle.getFrameRect().pos.y << std::endl << std::endl;

  Circle circle(3.3, {4.4, 2.2});
  std::cout << "Circle : " << std::endl;
  OutDataShape(circle);
  std::cout << "S(circle) = " << circle.getArea() << std::endl;
  std::cout << "Spot of middle on Ox = " << circle.getFrameRect().pos.x << std::endl;
  std::cout << "Spot of middle on Oy = " << circle.getFrameRect().pos.y << std::endl << std::endl;
  std::cout << "After moving" << std::endl;
  circle.move({12.1, 11.1});
  std::cout << "S(circle) = " << circle.getArea() << std::endl;
  std::cout << "Spot of middle on Ox = " << circle.getFrameRect().pos.x << std::endl;
  std::cout << "Spot of middle on Oy = " << circle.getFrameRect().pos.y << std::endl << std::endl;
  std::cout << "After moving" << std::endl;
  circle.move(2.8, 2.5);
  std::cout << "S(circle) = " << circle.getArea() << std::endl;
  std::cout << "Spot of middle on Ox = " << circle.getFrameRect().pos.x << std::endl;
  std::cout << "Spot of middle on Oy = " << circle.getFrameRect().pos.y << std::endl << std::endl;

  Triangle triangle({2.3, 5.4}, {3.8, 2.3}, {0.8, 1.4});
  std::cout << "Triangle : " << std::endl;
  OutDataShape(triangle);
  std::cout << "S(triangle) = " << triangle.getArea() << std::endl;
  std::cout << "Spot of middle on Ox = " << triangle.spotofcenter().x << std::endl;
  std::cout << "Spot of middle on Oy = " << triangle.spotofcenter().y << std::endl << std::endl;
  std::cout << "After moving:" << std::endl;
  triangle.move({1.0, 2.0});
  std::cout << "S(triangle) = " << triangle.getArea() << std::endl;
  std::cout << "Spot of middle on Ox = " << triangle.spotofcenter().x << std::endl;
  std::cout << "Spot of middle on Oy = " << triangle.spotofcenter().y << std::endl << std::endl;
  std::cout << "After moving" << std::endl;
  triangle.move(3.0, 4.0);
  std::cout << "S(triangle) = " << triangle.getArea() << std::endl;
  std::cout << "Spot of middle on Ox = " << triangle.spotofcenter().x << std::endl;
  std::cout << "Spot of middle on Oy = " << triangle.spotofcenter().y << std::endl;
  return 0;
}
