#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

using namespace kudryakov;

int main()
{
  Rectangle rectangle({-2,0}, 2, 2);
  Circle circle({2,0}, 1);
  
  CompositeShape cs(&rectangle);
  cs.addShape(&circle);
  
  std::cout << "Area: " << cs.getArea() << std::endl;
  std::cout << "Pos X: " << cs.getFrameRect().pos.x << std::endl
    << "Pos Y: " << cs.getFrameRect().pos.y << std::endl;
  std::cout << "Width: " << cs.getFrameRect().width << std::endl;
  std::cout << "Heigth: " << cs.getFrameRect().height << std::endl;
  
  cs.scale(2);
  std::cout << "Composite Shape was scaled by 2" << std::endl;
  
  std::cout << "Area: " << cs.getArea() << std::endl;
  std::cout << "Pos X: " << cs.getFrameRect().pos.x << std::endl
    << "Pos Y: " << cs.getFrameRect().pos.y << std::endl;
  std::cout << "Width: " << cs.getFrameRect().width << std::endl;
  std::cout << "Heigth: " << cs.getFrameRect().height << std::endl;
  
  return 0;
}
