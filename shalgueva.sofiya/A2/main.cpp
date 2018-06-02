#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  try
  {
    shalgueva::point_t point = {30.0, 130.0};

    shalgueva::Rectangle r({30.0, 70.0, point});
    shalgueva::Shape *rectangle = & r;
    std::cout << "Area of rectangle " << rectangle -> getArea() << std::endl;
    rectangle -> getFrameRect();
    rectangle -> move(70.0, -30.0);
    std::cout << "After moving" << std::endl;
    rectangle -> scale(2.0);
    std::cout << "Area of rectangle " << rectangle -> getArea() << std::endl;
    rectangle -> getFrameRect();

    shalgueva::Circle c({200.0, 130.0}, 25.0);
    shalgueva::Shape *circle = & c;
    std::cout << "Area of circle " << circle -> getArea() << std::endl;
    circle -> getFrameRect();
    circle -> move({10.0, 10.0});
    std::cout << "After moving" <<std::endl;
    circle -> scale(0.9);
    std::cout << "Area of circle " << circle -> getArea() << std::endl;
    circle -> getFrameRect();
  }
  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}
