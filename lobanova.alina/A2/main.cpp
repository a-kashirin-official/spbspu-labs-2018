#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

using namespace lobanova;

int main()
{
  lobanova::Circle c = {{5, 5}, 3};
  std::cout << "Area of circle: " << c.getArea() << std::endl;
  lobanova::rectangle_t i = c.getFrameRect();
  lobanova::Rectangle rect = {i.pos, i.width, i.height};
  c.scale(2);
  std::cout << "Area of circle after scaling(2): " << c.getArea() << std::endl;
  std::cout << "Area of rectangle: " << rect.getArea() << std::endl;
  rect.scale(0.5);
  std::cout << "Area of rectangle after scaling(0.5): " << rect.getArea() << std::endl;

}
