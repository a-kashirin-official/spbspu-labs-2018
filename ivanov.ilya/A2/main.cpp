#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include <iostream>

using namespace ivanov;

int main (int, char *[])
{
  try
  {
    Rectangle rect{ { {7.0, 7.0}, 15.0, 25.0}};
    Circle circ{{4.0, 3.0}, 10.0};
    Triangle trian{ {1.0, 0.0}, {12.0, 12.0}, {20.0, 1.0}  };
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
    std::cout << "Object after scaling" << "\n";
    rect.scale(3.0);
    circ.scale(2.0);
    trian.scale(4.0);
  }
  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  return 0;
}
