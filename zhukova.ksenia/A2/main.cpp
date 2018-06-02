
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"

using namespace zhukova;

int main()
{
  try
  {
    std::cout << "Rectangle" << std::endl;

    Rectangle rect( { 0.0, 0.0 }, 13.0, 17.0 );
    Shape * ptr = &rect;

    std::cout << "Rectangle width is " << std::fixed << std::setprecision(2) << ptr->getFrameRect().width
        << "Rectangle height is " << ptr->getFrameRect().height << std::endl;
    std::cout << "Area before scaling was " << ptr->getArea() << std::endl;

    ptr->scale(7.0);
    std::cout << "Area after scaling is " << ptr->getArea() << std::endl;


    std::cout << "Circle" << std::endl;

    Circle circ( { 7.0, 7.0 }, 11.0 );
    ptr = &circ;

    std::cout << "Circle radius is " << ptr->getFrameRect().width / 2 << std::endl;
    std::cout << "Area before scaling was " << ptr->getArea() << std::endl;

    ptr->scale(3.0);
    std::cout << "Area after scaling is " << ptr->getArea() << std::endl;
  }
  catch (std::invalid_argument &exception)
  {
    std::cerr << exception.what() << std::endl;
    return 1;
  }

  return 0;
}
