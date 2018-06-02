#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

using namespace tseptsov;

void OutDataShape(const Shape &shape)
{
  shape.OutData();
}

int main()
{

  try {
    Rectangle rectangle(1.0, 20.0, {13.0, 13.0});
    std::cout << "RECTANGLE" << std::endl;
    OutDataShape(rectangle);
    std::cout << "Rectangle area =  " << rectangle.getArea() << std::endl;
    rectangle.scale(2.0);
    std::cout << "Scaled rectangle =  " << rectangle.getArea() << std::endl << std::endl;

    Circle circle(30.0, {13.0, 28.0});
    std::cout << "CIRCLE" << std::endl;
    OutDataShape(circle);
    std::cout << "Circle area = " << circle.getArea() << std::endl;
    circle.scale(2.0);
    std::cout << "Scaled circle = " << circle.getArea() << std::endl << std::endl;
    
    Triangle triangle({12.0, 13.0}, {50.0, 60.0}, {19.0, 18.0});
    std::cout << "TRIANGLE" << std::endl;
    OutDataShape(triangle);
    std::cout << "Triangle area = " << triangle.getArea() << std::endl;
    triangle.scale(2.0);
    std::cout << "Scaled triangle = " << triangle.getArea() << std::endl << std::endl;
  }
  catch (std::invalid_argument &error) {
    std::cerr << error.what() << std::endl;
    return 1;
  }

  return 0;
}

