#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  Rectangle rect(11, 5, {7, 9});
  Shape *shrect = &rect;
  rect.printParameters();
  std::cout << "Rectangle area=" << shrect -> getArea() << std::endl;
  std::cout << "Width, height and center of frame rectangle "; 
  std::cout << shrect -> getFrameRect().width << ", ";
  std::cout << shrect -> getFrameRect().height << " (";
  std::cout << shrect -> getFrameRect().pos.x << ", ";
  std::cout << shrect -> getFrameRect().pos.y << ")" << std::endl;
  point_t const point{8, 4};
  std::cout << "Move to point (8, 4)" << std::endl;
  shrect -> move(point);
  std::cout << "New rectangle center";
  rect.printCenter();
  std::cout << "Move on (8, 4)" << std::endl;
  shrect -> move(8, 4);
  std::cout <<"New rectangle center";
  rect.printCenter();
  Circle cir(6, {2, 10});
  Shape *shcir = &cir;
  cir.printParameters();
  std::cout << "Width, height and center of frame rectangle ";
  std::cout << shcir -> getFrameRect().width << ", ";
  std::cout << shcir -> getFrameRect().height << " (";
  std::cout << shcir -> getFrameRect().pos.x << ", ";
  std::cout << shcir -> getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Circle area=" << shcir -> getArea() << std::endl;
  std::cout << "Move to point (8, 4)" << std::endl;
  shcir -> move(point);
  std::cout << "New circle center ";
  cir.printCenter();
  std::cout << "Move on (5, 3)" << std::endl;
  shcir -> move(5, 3);
  std::cout << "New circle center ";
  cir.printCenter();
  return 0;
}
