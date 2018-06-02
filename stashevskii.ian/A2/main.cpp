#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

using namespace stashevskii;

void printFrameRectangle(const Shape &shape, const char *name)
{
  rectangle_t objectFrame = shape.getFrameRect();
  std::cout << "Frame rectangle for the "<< name << ":"
      << " Width: " << objectFrame.width
      << " Height: " << objectFrame.height
      << " Position:"  << " x: " << objectFrame.pos.x
      << " y: " << objectFrame.pos.y << std::endl;
}


int main()
{
  Rectangle rect({ 4.5, 3.5,{2, 1}});
  rect.printf();
  std::cout << "Move by point" << std::endl;
  rect.move({2, 8});
  rect.printf();
  std::cout << "Move by shift" << std::endl;
  rect.move( 4, 4 );
  rect.printf();
  printFrameRectangle(rect, "rectangle");
  std::cout << "__________________________________" << std::endl;
  Circle circl({ 4,{5, 6}});
  circl.printf();
  std::cout << "Move by point" << std::endl;
  circl.move({3, 6});
  circl.printf();
  std::cout << "Move by shift" << std::endl;
  circl.move( 4, 2 );
  circl.printf();
  printFrameRectangle(circl, "circle");
  return 0;
}
