#include "circle.hpp"
#include "rectangle.hpp"
#include <iostream>
#include <cmath>

int main()
{
  std::cout << "!RECTANGLE!" << std::endl;
  Rectangle rect({0.0,0.0}, 30.2, 10.3);
  Shape * uk = &rect;
  std::cout << "Center of rectangle = {" << uk->getFrameRect().pos.x << "," << uk->getFrameRect().pos.y << "}" << std::endl;
  std::cout << "Width of frame = " << uk->getFrameRect().width << std::endl;
  std::cout << "Height of frame = " << uk->getFrameRect().height << std::endl;
  std::cout << "Area of rectangle = " << uk->getArea() << std::endl;
  uk->move({30.4,10.3});
  std::cout << "Move to {30.4,10.3}" << std::endl;
  std::cout << "Center of rectangle = {" << uk->getFrameRect().pos.x << "," << uk->getFrameRect().pos.y << "}" << std::endl;
  uk->move(20.6,40.2);
  std::cout << "Move on (20.6,40.2)" << std::endl;
  std::cout << "Center of rectangle = {" << uk->getFrameRect().pos.x << "," << uk->getFrameRect().pos.y << "}" << std::endl;

  std::cout << " " << std::endl;
  std::cout << "!CIRCLE!" << std::endl;
  Circle circ({0.0,0.0}, 30.8);
  uk = &circ;
  std::cout << "Center of circle = {" << uk->getFrameRect().pos.x << "," << uk->getFrameRect().pos.y << "}" << std::endl;
  std::cout << "Width of frame = " << uk->getFrameRect().width << std::endl;
  std::cout << "Height of frame = " << uk->getFrameRect().height << std::endl;
  std::cout << "Area of circle = " << uk->getArea() << std::endl;
  uk->move({15.4,10.9});
  std::cout << "Move to {15.4,10.9}" << std::endl;
  std::cout << "Center of circle = {" << uk->getFrameRect().pos.x << "," << uk->getFrameRect().pos.y << "}" << std::endl;
  uk->move(40.4,10.1);
  std::cout << "Move on (40.4,10.1)" << std::endl;
  std::cout << "Center of circle = {" << uk->getFrameRect().pos.x << "," << uk->getFrameRect().pos.y << "}" << std::endl;
  return 0;
}
