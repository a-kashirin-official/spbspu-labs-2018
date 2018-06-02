#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

void testScaleMethod(marchenko::Shape &thisObject)
{
  std::cout << "Initial area of this figure is " << thisObject.getArea() << std::endl;
  std::cout << "Coefficient of scale is 12." << std::endl;
  double coeff = 12.0;
  thisObject.scale(coeff);
  std::cout << "New area of this figure is " << thisObject.getArea() << std::endl;
}
int main()
{
  marchenko::point_t center = { 250.0 , 250.0 };
  marchenko::Rectangle rect(100.0, 200.0, center);
  marchenko::Circle circle(center, 10.0);
  std::cout << "Testing scale method of rectangle : " << std::endl;
  testScaleMethod(rect);
  std::cout << "Testing scale method of circle : " << std::endl;
  testScaleMethod(circle);
  return 0;
}
