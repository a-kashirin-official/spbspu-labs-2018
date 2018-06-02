#include <cstdlib>
#include <iostream>

#include "../common/base-types.hpp"
#include "../common/circle.hpp"
#include "../common/rectangle.hpp"

using namespace razuvaev;

int main()
{
  try
  {
    Rectangle rectangle(3, 3, 10, 15);
    rectangle.move({5, 10});
    rectangle.move(2, 3);
    rectangle.scale(0.1);
    rectangle.writeInfoOfObject();
    std::cout<<std::endl;

    Circle circle(5, 5, 5);
    circle.move({100, 100});
    circle.move(5, 5);
    circle.scale(0.2);
    circle.writeInfoOfObject();
  }
  catch (const std::exception& e)
  {
    std::cout<<e.what();
    return 1;
  }
  return 0;
}
