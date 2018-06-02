#include <iostream>
#include <string>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"

using namespace golyshev;

int main()
{
  try {
    Rectangle rectangle(1.0, 1.0, {-1.0, -1.0});
    Circle circle(1.0, {3.0, 3.0});
    Triangle triangle({0.0, 0.0}, {2.0, 2.0}, {4.0, 0.0});

    std::shared_ptr<golyshev::Shape> circle_ptr = std::make_shared<golyshev::Circle>(circle);
    std::shared_ptr<golyshev::Shape> rectangle_ptr = std::make_shared<golyshev::Rectangle>(rectangle);
    std::shared_ptr<golyshev::Shape> triangle_ptr = std::make_shared<golyshev::Triangle>(triangle);

    std::cout << "Creating an array from a circle, rectangle and triangle" << std::endl;
    golyshev::CompositeShape arr(circle_ptr);
    arr.add(rectangle_ptr);
    arr.add(triangle_ptr);
    arr.OutInf();

    std::cout << "Scale: 2" << std::endl;
    arr.scale(2);
    arr.OutInf();

    std::cout << "Move by dx, dy: " << std::endl;
    arr.move(2, 2);
    arr.OutInf();

    std::cout << "Move to point: " << std::endl;
    arr.move({2, 2});
    arr.OutInf();

    std::cout << "Delete triangle from array " << std::endl;
    arr.remove(2);
    arr.OutInf();
  }
  catch (std::exception &error) {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}
