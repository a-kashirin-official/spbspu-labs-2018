#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

void testScaleFunction(kadyrov::Shape &currentObject)
{
  std::cout<< "Starting area of current object is " << currentObject.getArea() << std::endl;
  currentObject.scale(5.0);
  std::cout<<"Scale's coefficient is 5.0" << std::endl;
  std::cout<<"New area of current object is" << currentObject.getArea() << std::endl;
}

int main()
{
  try
  {
    kadyrov::Rectangle rect({ 100.0, 200.0, { 100.0, 100.0 } });
    kadyrov::Circle circle({ 100.0, 100.0 }, 20.0);
    std::cout << "Testing scale function for rectangle" << std::endl;
    testScaleFunction(rect);
    std::cout << "Testing scale function for circle" << std::endl;
    testScaleFunction(circle);
  }
  catch (const std::invalid_argument &ex){}
  return 0;
}
