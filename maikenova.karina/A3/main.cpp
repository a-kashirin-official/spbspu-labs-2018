#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

void testShape(const maikenova::Shape & newShape)
{
  std::cout << "   Current position: (" << newShape.getPos().x << ", " << newShape.getPos().y << ");" << std::endl;
  std::cout << "   Area: " << newShape.getArea() << std::endl;
  maikenova::rectangle_t myFrame = newShape.getFrameRect();
  std::cout << "   Details of the framed rectangle: " << std::endl;
  std::cout << "    Position: (" << myFrame.pos.x << ", " << myFrame.pos.y << ")" << std::endl;
  std::cout << "    Height: " << myFrame.height << "; Width: " << myFrame.width << "\n\n" << std::endl;
}

int main()
{
  maikenova::Circle myCircle({5.0, 5.0}, 2.0);
  maikenova::Rectangle myRectangle({9.0, 9.0}, 4.0, 2.0);
  maikenova::CompositeShape myComp;

  myComp.pushBack(& myCircle);
  myComp.pushBack(& myRectangle);

  std::cout << "DETAILS OF THE COMPOSITE SHAPE:" << std::endl;
  std::cout <<"  Initital details: " << std::endl;
  testShape(myComp);

  std::cout << "  After shifting by " << 5.0 << " in x-axis and " << 5.0 << " in y-axis: " << std::endl;
  myComp.move(5.0, 5.0);
  testShape(myComp);

  std::cout << "  After moving to point (" << 100.0 << ", " << 100.0 << "): " << std::endl;
  myComp.move({100.0, 100.0});
  testShape(myComp);

  std::cout << "  After scaling by " << 2 << ": " << std::endl;
  myComp.scale(2);
  testShape(myComp);

  return 0;
}

