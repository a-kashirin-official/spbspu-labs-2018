#include "rectangle.hpp"
#include "circle.hpp"
#include <iostream>

int main()
{
  kahuanahil::Rectangle rect(10.0, 12.0, {2.0, 3.0});
  kahuanahil::Shape * poi = &rect;
  std::cout << "Rectangle area before scale " << poi->getArea() << std::endl;
  std::cout << "Width and Height before scale (" << rect.getFrameRect().width << "; " << rect.getFrameRect().height << ")" << std::endl;
  poi->scale(2.0);
  std::cout << "Factor = 2, rectangle area after scale " << poi->getArea() << std::endl;
  std::cout << "Width and Heigh after scale (" << rect.getFrameRect().width << "; " << rect.getFrameRect().height << ")" << std::endl;

  kahuanahil::Circle cir(2.0, {5.0, 6.0});
  kahuanahil::Shape * po = &cir;
  std::cout << "Circle area before scale " << po->getArea() << std::endl;
  std::cout << "Diameter before scale = " << cir.getFrameRect().height << std::endl;
  po->scale(3.0);
  std::cout << "Factor = 3, cirlce area after scale " << po->getArea() << std::endl;
  std::cout << "Diameter after scale  = " << cir.getFrameRect().width << std::endl;
 
  return 0;

}
