#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include <iostream>

int main (int, char *[])
{
  try
  {
    Rectangle rect{ { {7.0, 7.0}, 15.0, 25.0}};
    Circle circ{{4.0, 3.0}, 10.0};
    Triangle trian{ {1, 0}, {12, 12}, {20, 1}  };
    rect.show();
    circ.show();
    trian.show();
    const point_t to = {30.0, 40.0};
    rect.move(to);
    circ.move(10.0, 10.0);
    trian.move(to);
    std::cout << "----Objects after moving------" << "\n";
    rect.show();
    circ.show();
    trian.show();
  }
  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  return 0;
}
