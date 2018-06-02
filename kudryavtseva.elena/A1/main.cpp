#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  point_t t = {7.0,9.0};
  point_t k;
  Rectangle rect( {4.0,10.0}, 3.0, 5.0);
  std::cout << "\n" << std::endl;
  std::cout << "FOR THE RECTANGLE :" << std::endl;
  k = rect.getPos();
  std::cout << "Coordinates of the center: " << k.x << "  " << k.y << std::endl;
  rect.move(2.0, 5.0);
  k = rect.getPos();
  std::cout << "New coordinates of the center after moving by dx, dy: " << k.x << "  " << k.y << std::endl;
  rect.move(t);
  rect.printf();

  t = {5.0,8.0};
  Circle circ({2.0,5.0},2.0);
  std::cout << "\n" << std::endl;
  std::cout << "FOR THE CIRCLE :" << std::endl;
  k = circ.getPos();
  std::cout << "Coordinates of the center: " << k.x << "  " << k.y << std::endl;
  circ.move(11.0, 2.0);
  k = circ.getPos();
  std::cout << "New coordinates of the center after moving by dx, dy: " << k.x << "  " << k.y << std::endl;
  circ.move(t);
  circ.printf();

  return 0;
}
