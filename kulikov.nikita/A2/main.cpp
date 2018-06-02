#include "rectangle.hpp"
#include "circle.hpp"
#include <iostream>
using namespace kulikov;


int main (int, char *[])
{
  try
  {
    Rectangle rect{ { {7.0, 7.0}, 15.0, 25.0}};
    Circle circ{{4.0, 3.0}, 10.0};
    double koefficient = 3.0;
    rect.scale(koefficient);
    circ.scale(koefficient);
    const point_t to = {30.0, 40.0};
    rect.move(to);
    circ.move(10.0, 10.0);
  }
  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  return 0;
}
