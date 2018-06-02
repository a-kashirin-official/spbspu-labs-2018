#include <iostream>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"

using namespace volkov;

int main()
{
  try
  {
    Rectangle rad({17, 22}, 9, 12);
    std::cout << "Creating Rectangle x=17, y=22, w=9, h=12" << std::endl;
    std::cout << rad << std::endl;
    rad.move(5, 9);
    std::cout << "Moving Rectangle by dx=5, dy=9" << std::endl;
    std::cout << rad << std::endl;
    rad.move({21.33, 10.23});
    std::cout << "Moving Rectangle to point x=21.33, y=10.23" << std::endl;
    std::cout << rad << std::endl;
    rad.scale(4);
    std::cout << "scaled rectangle" << std::endl;
    std::cout << rad << std::endl;
  }
  catch (const std::invalid_argument &t)
  {
    std::cerr << t.what() << std::endl;
    return 1;
  }

  try
  {
    Circle cir({12.0, 17.0}, 5.0);
    std::cout << "Creating Circle x=12.0, y=17.0, r=5" << std::endl;
    std::cout << cir << std::endl;

    cir.move(7, 11);
    std::cout << "Moving Circle by dx=7, dy=1" << std::endl;
    std::cout << cir << std::endl;

    cir.move({14.27, 10.66});
    std::cout << "Moving Circle to point x=14.27, y=10.66" << std::endl;
    std::cout << cir << std::endl;

    cir.scale(5);
    std::cout << "scaled circle" << std::endl;
    std::cout << cir << std::endl;
  }
  catch (const std::invalid_argument & t)
  {
    std::cerr << t.what() << std::endl;
    return 1;
  }

  return 0;
}
