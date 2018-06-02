#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

  
using namespace reznikov;
  
void printFrameRectangle(const Shape &shape, const char *name)
{
  rectangle_t objectFrame = shape.getFrameRect();
  std::cout << "Frame rectangle for the"<< name << ":" << std::endl;
  std::cout << "  Width: " << objectFrame.width << std::endl;
  std::cout << " Height: " << objectFrame.height << std::endl;
  std::cout << "  Position:" << std::endl;
  std::cout << "    x: " << objectFrame.pos.x << std::endl;
  std::cout << "    y: " << objectFrame.pos.y << std::endl;
}

int main()
{
  Circle circle({1.5,{3.8, 2.6} });

  std::cout << "That we have: " << std::endl;
  circle.inf();

  std::cout << "Move circle 9 left and 2  up " << std::endl;
  circle.move(9, 2);
  circle.inf();

  std::cout << "Move circle to a  point (7, 8). " << std::endl;
  circle.move({7, 8});
  circle.inf();

  std::cout << "Magnify circle in four times." << std::endl;
  circle.scale(4);
  circle.inf();
  
  printFrameRectangle(circle, "circle");


  Rectangle rectangle({8.0, 6.5, {1.0, 2.0} });

  std::cout << "That we have:" << std::endl;
  rectangle.inf();

  std::cout << "Move rectangle 12 right and 3  down" << std::endl;
  rectangle.move(-12, -3);
  rectangle.inf();

  std::cout << "Move rectangle to a  point (7, 8)." << std::endl;
  rectangle.move({7, 8});
  rectangle.inf();

  std::cout << "Magnify rectangle in two times." << std::endl; 
  rectangle.scale(2);
  rectangle.inf();
  
  printFrameRectangle(rectangle, "rectangle");

  return 0;
}
