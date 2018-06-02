#include <iostream>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"

using namespace nasirov;

int main()
{
  try
  {
    Rectangle shape_1({0, 0}, 30, 10);
    Shape *rectangle = &shape_1;
    std::cout << "rectangle was created" << std::endl << std::endl;

    rectangle->printData();

    double dx = 10;
    double dy = -5;

    rectangle->move(dx, dy);
    std::cout << " << std::endlrectangle was moved on (" << dx << ", " << dy << ")" << std::endl << std::endl;

    rectangle->printData();

    Circle shape_2({3, -2}, 5);
    Shape *circle = &shape_2;
    std::cout << " << std::endlcircle was created << std::endl << std::endl";

    circle->printData();

    point_t pos = {-10, 1};

    circle->move(pos);
    std::cout << std::endl << "circle was moved to {" << pos.x << ", " << pos.y << "}" << std::endl << std::endl;

    circle->printData();
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  return 0;
}
