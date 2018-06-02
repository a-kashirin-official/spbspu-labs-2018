#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"

void showInfo(const suslov::Shape & shape)
{
  std::cout << "Width of the frame: ";
  std::cout << shape.getFrameRect().width << std::endl;
  std::cout << "Height of the frame: ";
  std::cout << shape.getFrameRect().height << std::endl;
  std::cout << "Center of the frame (" << shape.getFrameRect().pos.x << " , "
  << shape.getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Area: ";
  std::cout << shape.getArea() << std::endl << std::endl;
 }

int main()
{
  suslov::Rectangle rectangle({200, 100}, 50, 30);
  suslov::Circle circle( {400, 200}, 45 );

  std::cout << "Rectangle info: " << std::endl;
  showInfo(rectangle);

  std::cout << "Circle info: " << std::endl;
  showInfo(circle);

  std::cout<< "Scale rectangle x2" << std::endl;
  std::cout<< "Scale circle x2" << std::endl << std::endl;

  rectangle.scale(2);
  circle.scale(2);

  std::cout << "Rectangle info: " << std::endl;
  showInfo(rectangle);

  std::cout << "Circle info: " << std::endl;
  showInfo(circle);

  std::cout << "Move rectangle to (300,300)" << std::endl << std::endl;
  rectangle.move({300, 300});
  showInfo(rectangle);

  std::cout << "Move circle x+20, y+40" << std::endl << std::endl;
  circle.move(20, 40);
  showInfo(circle);

  return 0;
}
