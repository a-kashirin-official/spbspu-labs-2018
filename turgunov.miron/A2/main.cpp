#include <iostream>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"

using namespace turgunov;

int main()
{
  try
  {
    Rectangle shape_1({0, 0}, 30, 10);
    Shape *rectangle = &shape_1;
    rectangle->printInfo();
    
    std::cout << "Area is = " << rectangle->getArea() << "\n";
    
    std::cout << "Shape move to {10, 2}\n";
    rectangle->move({10, 2});
    rectangle->printInfo();
    
    std::cout << "Shape move on (5, -20)\n";
    rectangle->move(5, -20);
    rectangle->printInfo();
    std::cout << "\n";

    Circle shape_2({0, 0}, 5);
    Shape *circle = &shape_2;
    circle->printInfo();

    std::cout << "Area is = " << circle->getArea() << "\n";
    
    std::cout << "Shape move to {-6, 3}\n";
    circle->move({-6, 3});
    circle->printInfo();
    
    std::cout << "Shape move on (8, 14)\n";
    circle->move(8, 14);
    circle->printInfo();
    std::cout << "\n";
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}
