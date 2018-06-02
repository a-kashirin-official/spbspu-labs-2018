#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

void printFrameRectangle(const Shape &shape, const char *name)
{
  rectangle_t objectFrame = shape.getFrameRect();
  std::cout << "Frame rectangle for the"<< name << ":"
  << "  Width: " << objectFrame.width
  << " Height: " << objectFrame.height
  << "  Position:"
  << "    x: " << objectFrame.pos.x
  << "    y: " << objectFrame.pos.y << std::endl;
}

int main()
{
  Circle circle({ 1.5,{ 3.8, 2.6 } });

  std::cout << "That we have:\n";
  circle.inf();

  std::cout << "Move circle 9 left and 2  up.\n";
  circle.move( 9, 2);
  circle.inf();

  std::cout << "Move circle to a  point (7, 8).\n";
  circle.move({ 7, 8 });
  circle.inf();
  
  printFrameRectangle(circle, "circle");

  std::cout << "=========================" << std::endl;


  Rectangle rectangle({ 8.0, 6.5,{ -1.0, -2.0 } });

  std::cout << "That we have:\n";
  rectangle.inf();

  std::cout << "Move rectangle 12 right and 3  down.\n";
  rectangle.move( -12, -3);
  rectangle.inf();

  std::cout << "Move rectangle to a  point (7, 8).\n";
  rectangle.move({ 7, 8});
  rectangle.inf();

  printFrameRectangle(rectangle, "rectangle");
  
  return 0;

}

