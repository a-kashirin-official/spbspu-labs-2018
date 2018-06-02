#include <iostream>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

using namespace stankeviciute;

int main()
{
  try
  {
    Rectangle shape_1({0, 0}, 30, 10);
    Shape *rectangle = &shape_1;
    std::cout << "rectangle was created\n\n";

    rectangle->printData();

    double dx = 10;
    double dy = -5;

    rectangle->move(dx, dy);
    std::cout << "\nrectangle was moved on (" << dx << ", " << dy << ")\n\n";

    rectangle->printData();

    Circle shape_2({3, -2}, 5);
    Shape *circle = &shape_2;
    std::cout << "\ncircle was created\n\n";

    circle->printData();

    point_t pos = {-10, 1};

    circle->move(pos);
    std::cout << "\ncircle was moved to {" << pos.x << ", " << pos.y << "}" << "\n\n";

    circle->printData();

    Triangle shape_3({0, 0}, {0, 4}, {3, 0});
    Shape *triangle = &shape_3;
    std::cout << "\ntriangle was created\n\n";

    triangle->printData();

    pos = {4, 9};

    triangle->move(pos);
    std::cout << "\ntriangle was moved to {" << pos.x << ", " << pos.y << "}" << "\n\n";

    double k = 2;

    triangle->scale(k);
    std::cout << "\ndimensions of the triangle increased " << k << " times\n\n";

    triangle->printData();
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}
