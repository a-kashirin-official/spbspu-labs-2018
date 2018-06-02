#include <iostream>

#include "circle.hpp"
#include "rectangle.hpp"

using namespace rebrin;

int main()
{
  try
  {
    Shape *my_pointer;
    my_pointer = new Rectangle({10.0, 15.0, {0.0, 0.0}});

    std::cout << "RECTANGLE Default parameters: x: 0, y: 0, width: 10, height: 15" << std::endl;
    std::cout << "X: " << my_pointer->getFrameRect().pos.x << std::endl;
    std::cout << "Y: " << my_pointer->getFrameRect().pos.y << std::endl;
    std::cout << "Width: " << my_pointer->getFrameRect().width << std::endl;
    std::cout << "Height: " << my_pointer->getFrameRect().height << std::endl;

    std::cout << "GETTING AREA" << std::endl;
    std::cout << my_pointer->getArea() << std::endl;

    std::cout << "RECTANGLE SCALE x2" << std::endl;
    my_pointer->scale(2);

    std::cout << "Width: " << my_pointer->getFrameRect().width << std::endl;
    std::cout << "Height: " << my_pointer->getFrameRect().height << std::endl;

    std::cout << "GETTING AREA after scaling" << std::endl;
    std::cout << my_pointer->getArea() << std::endl;


    delete my_pointer;

    my_pointer = new Circle({1, 5}, 10);

    std::cout << "CIRCLE Default parameters: x: 1, y: 5, radius: 10" << std::endl;
    std::cout << "X: " << my_pointer->getFrameRect().pos.x << std::endl;
    std::cout << "Y: " << my_pointer->getFrameRect().pos.y << std::endl;
    std::cout << "Diameter: " << my_pointer->getFrameRect().width << std::endl;

    std::cout << "GETTING AREA" << std::endl;
    std::cout << my_pointer->getArea() << std::endl;

    std::cout << "CIRCLE SCALE x3" << std::endl;
    my_pointer->scale(3);

    std::cout << "Diameter: " << my_pointer->getFrameRect().width << std::endl;

    std::cout << "GETTING AREA after scaling" << std::endl;
    std::cout << my_pointer->getArea() << std::endl;

    delete my_pointer;
  }
  catch (std::exception & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }

  return 0;
}
