#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include <iostream>

void information(const Shape & figure)
{
  std::cout << "Area=" << figure.getArea() << std::endl;
  std::cout << "FrameRect: width, height: " << figure.getFrameRect().width << ", ";
  std::cout << figure.getFrameRect().height << std::endl;
  std::cout << "FrameRect: x, y: " << figure.getFrameRect().pos.x << ", " << figure.getFrameRect().pos.y << std::endl;
}

int main()
{
  Rectangle rect(10, 5, { 3, 4 });
  Circle circ(1, { 5, 5 });
  Triangle triang({ 1, 1 }, { -5, 1 }, { 4, 3 });

  try {
    std::cout << "Rectangle" << std::endl;
    information(rect);
    rect.move(5, 5);
    std::cout << "move={5, 5}" << std::endl;
    information(rect);

    std::cout << "Circle" << std::endl;
    information(circ);
    circ.move(2, 3);
    std::cout << "move={2, 3}" << std::endl;
    information(circ);

    std::cout << "Triangle" << std::endl;
    information(triang);
    triang.move(1, 2);
    std::cout << "move={1, 2}" << std::endl;
    information(triang);
  }
  catch(const std::invalid_argument &e) {
    std::cerr << e.what() <<std::endl;
    return 1;
  }
  return 0;
}
