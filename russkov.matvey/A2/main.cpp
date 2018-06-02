#include <iostream>
#include "base-types.hpp"
#include "shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  std::cout << "Creating a rectangle:\n";
  std::cout << "Center: x = 6, y = 10;\n";
  std::cout << "Width = 20, Height = 30\n";

  russkov::point_t point = {6.0, 10.0};
  russkov::Rectangle rec(point, 20.0, 30.0);

  std::cout << "Rectangle scaling: coefficient = 5\n";
  rec.scale(5.0);

  std::cout << "Creating a circle:\n";
  std::cout << "Center: x = 7, y = 14;\n";
  std::cout << "Radius = 9\n";

  point = {7.0, 14.0};
  russkov::Circle cir(point, 9.0);

  std::cout << "Circle scaling: coefficient = 5\n";
  cir.scale(5.0);
  return 0;
}
