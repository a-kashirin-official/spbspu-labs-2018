#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  try
  {

  Circle circle1( {-5, 5}, 5 );
  Rectangle rectangle1( { {5, 5}, 10, 10} );

  Shape * pShape;
  pShape = &circle1;

  std::cout << "Circle coordinates: " << pShape->getFrameRect().pos.x << " " << pShape->getFrameRect().pos.y << std::endl;
  std::cout << "Frame Size " << pShape->getFrameRect().width << "*" << pShape->getFrameRect().height << std::endl;
  std::cout << "Circle Area " << pShape->getArea() << std::endl;
  pShape->move(-5, -5);
  std::cout << "Circle coordinates (shift -5 -5): " << pShape->getFrameRect().pos.x << " " << pShape->getFrameRect().pos.y << std::endl;
  pShape->move({6, 6});
  std::cout << "Circle coordinates (moved to 6 6): " << pShape->getFrameRect().pos.x << " " << pShape->getFrameRect().pos.y << std::endl;
  
  pShape = &rectangle1;

  std::cout << "Rectangle coordinates: " << pShape->getFrameRect().pos.x << " " << pShape->getFrameRect().pos.y << std::endl;
  std::cout << "Frame Size " << pShape->getFrameRect().width << "*" << pShape->getFrameRect().height << std::endl;
  std::cout << "Rectangle Area " << pShape->getArea() << std::endl;
  pShape->move(-5, -5);
  std::cout << "Rectangle coordinates (shift -5 -5): " << pShape->getFrameRect().pos.x << " " << pShape->getFrameRect().pos.y << std::endl;
  pShape->move({6, 6});
  std::cout << "Rectangle coordinates (moved to 6 6): " << pShape->getFrameRect().pos.x << " " << pShape->getFrameRect().pos.y << std::endl;

  } catch ( std::invalid_argument & smth ) 
  {
    std::cerr << smth.what() << std::endl;
    return 1; 
  }

  return 0;
}
