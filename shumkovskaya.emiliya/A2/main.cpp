#include <iostream>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"

using namespace shumkovskaya;

int main()
{
  //operations for rectangle
  try
  {
    Rectangle rect(11, 5, {7, 9});
    Shape *shrect = &rect;
    std::cout << "Width, height and center of frame rectangle ";
    std::cout << shrect -> getFrameRect().width << ", ";
    std::cout << shrect -> getFrameRect().height << " (";
    std::cout << shrect -> getFrameRect().pos.x << ", ";
    std::cout << shrect -> getFrameRect().pos.y << ")" << std::endl;
    std::cout << "Area of rectangle = " << std::endl;
    shrect -> getArea();
    point_t const point{8, 4};
    std::cout << "Move to point (8, 4) and increase by 3 times" << std::endl;
    shrect -> move(point);
    shrect -> scale(3);
    std::cout << "New width, height and center of frame rectangle ";
    std::cout << shrect -> getFrameRect().width << ", ";
    std::cout << shrect -> getFrameRect().height << " (";
    std::cout << shrect -> getFrameRect().pos.x << ", ";
    std::cout << shrect -> getFrameRect().pos.y << ")" << std::endl;
    std::cout << "New area of rectangle = " << std::endl;
    shrect -> getArea();
  }
  catch (std::invalid_argument &error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }  
  //operations for circle
  try
  {
    Circle cir(6, {2, 10});
    Shape *shcir = &cir;
    std::cout << "Width, height and center of frame rectangle ";
    std::cout << shcir -> getFrameRect().width << ", ";
    std::cout << shcir -> getFrameRect().height << " (";
    std::cout << shcir -> getFrameRect().pos.x << ", ";
    std::cout << shcir -> getFrameRect().pos.y << ")" << std::endl;
    std::cout << "Area of circle = " << std::endl;
    shcir -> getArea();
    std::cout << "Move on (5, 3) and reduse by 4 times" << std::endl;
    shcir -> move(5, 3);
    shcir -> scale(0.25);
    std::cout << "New width, height and center of frame rectangle ";
    std::cout << shcir -> getFrameRect().width << ", ";
    std::cout << shcir -> getFrameRect().height << " (";
    std::cout << shcir -> getFrameRect().pos.x << ", ";
    std::cout << shcir -> getFrameRect().pos.y << ")" << std::endl;
    std::cout << "New area of circle = " << std::endl;
    shcir -> getArea();
  }
  catch (std::invalid_argument &error)
  {
    std::cerr << error.what() << std::endl;
    return 2;
  }  
  return 0;
}
