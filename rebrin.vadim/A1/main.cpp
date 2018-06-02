#include <iostream>

#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  Shape *my_pointer;
  my_pointer = new Rectangle({10.0, 15.0, {0.0, 0.0}});

  rectangle_t frame_rectangle{};

  std::cout << "RECTANGLE Default parameters: x: 0, y: 0, width: 10, height: 15" << std::endl;
  std::cout << "X: " << my_pointer->getFrameRect().pos.x << std::endl;
  std::cout << "Y: " << my_pointer->getFrameRect().pos.y << std::endl;
  std::cout << "Width: " << my_pointer->getFrameRect().width << std::endl;
  std::cout << "Height: " << my_pointer->getFrameRect().height << std::endl;

  std::cout << "MOVING TO POINT (2; 5)" << std::endl;
  my_pointer->move({2, 5});
  std::cout << "X: " << my_pointer->getFrameRect().pos.x << std::endl;
  std::cout << "Y: " << my_pointer->getFrameRect().pos.y << std::endl;

  std::cout << "GETTING AREA" << std::endl;
  std::cout << my_pointer->getArea() << std::endl;

  std::cout << "GETTING FRAME RECTANGLE" << std::endl;
  frame_rectangle = my_pointer->getFrameRect();
  std::cout << "X: " << frame_rectangle.pos.x << std::endl;
  std::cout << "Y: " << frame_rectangle.pos.y << std::endl;
  std::cout << "Width: " << frame_rectangle.width << std::endl;
  std::cout << "Height: " << frame_rectangle.height << std::endl;

  delete my_pointer;

  my_pointer = new Circle({1, 5}, 10);


  std::cout << "CIRCLE Default parameters: x: 1, y: 5, radius: 10" << std::endl;
  std::cout << "X: " << my_pointer->getFrameRect().pos.x << std::endl;
  std::cout << "Y: " << my_pointer->getFrameRect().pos.y << std::endl;

  std::cout << "MOVING -3; 6" << std::endl;
  my_pointer->move(-3, 6);
  std::cout << "X: " << my_pointer->getFrameRect().pos.x << std::endl;
  std::cout << "Y: " << my_pointer->getFrameRect().pos.y << std::endl;

  std::cout << "GETTING FRAME RECTANGLE" << std::endl;
  frame_rectangle = my_pointer->getFrameRect();
  std::cout << "X: " << frame_rectangle.pos.x << std::endl;
  std::cout << "Y: " << frame_rectangle.pos.y << std::endl;
  std::cout << "Width: " << frame_rectangle.width << std::endl;
  std::cout << "Height: " << frame_rectangle.height << std::endl;

  std::cout << "GETTING AREA" << std::endl;
  std::cout << my_pointer->getArea() << std::endl;

  delete my_pointer;

  return 0;
}
