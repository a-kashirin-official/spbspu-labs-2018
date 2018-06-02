#include <cstdlib>
#include <iostream>

#include "base-types.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  try
  {
    Rectangle rectangle(3, 3, 10, 15);
    rectangle.writeInfoOfObject();
    rectangle.move({5, 10});
    rectangle.move(2, 3);
    rectangle.writeInfoOfObject();

    Circle circle(5, 5, 5);
    circle.writeInfoOfObject();
    circle.move({100, 100});
    circle.move(5, 5);
    circle.writeInfoOfObject();
  }
  catch (const std::exception& e)
  {
    std::cout<<e.what();
    return 1;
  }
  return 0;
}
