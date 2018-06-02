#include "circle.hpp"
#include "rectangle.hpp"
#include <iostream>

int main()
{
  std::cout << "!RECTANGLE!" << std::endl;
  revtova::Rectangle rect({0.0,0.0}, -30.3, 10.2);
  revtova::Shape * uk = &rect;
  std::cout << "Center of rectangle = {" << uk->getFrameRect().pos.x << "," << uk->getFrameRect().pos.y << "}" << std::endl;
  std::cout << "Width of frame = " << uk->getFrameRect().width << std::endl;
  std::cout << "Height of frame = " << uk->getFrameRect().height << std::endl;
  std::cout << "Area of rectangle = " << uk->getArea() << std::endl;
  uk->move({30.4,10.8});
  std::cout << "Move to {30.4,10.8}" << std::endl;
  std::cout << "Center of rectangle = {" << uk->getFrameRect().pos.x << "," << uk->getFrameRect().pos.y << "}" << std::endl;
  uk->move(20.4,40.7);
  std::cout << "Move on (20.4,40.7)" << std::endl;
  std::cout << "Center of rectangle = {" << uk->getFrameRect().pos.x << "," << uk->getFrameRect().pos.y << "}" << std::endl;
  uk->scale(10.3);
  std::cout << "Scale on 10.3" << std::endl;
  std::cout << "Width of frame = " << uk->getFrameRect().width << std::endl;
  std::cout << "Height of frame = " << uk->getFrameRect().height << std::endl;
  std::cout << "Area of rectangle = " << uk->getArea() << std::endl;

  std::cout << " " << std::endl;
  std::cout << "!CIRCLE!" << std::endl;
  revtova::Circle circ({0.0,0.0}, 30.5);
  uk = &circ;
  std::cout << "Center of circle = {" << uk->getFrameRect().pos.x << "," << uk->getFrameRect().pos.y << "}" << std::endl;
  std::cout << "Width of frame = " << uk->getFrameRect().width << std::endl;
  std::cout << "Height of frame = " << uk->getFrameRect().height << std::endl;
  std::cout << "Area of circle = " << uk->getArea() << std::endl;
  uk->move({15.5,10.1});
  std::cout << "Move to {15.5,10.1}" << std::endl;
  std::cout << "Center of circle = {" << uk->getFrameRect().pos.x << "," << uk->getFrameRect().pos.y << "}" << std::endl;
  uk->move(40.5,10.2);
  std::cout << "Move on (40.5,10.2)" << std::endl;
  std::cout << "Center of circle = {" << uk->getFrameRect().pos.x << "," << uk->getFrameRect().pos.y << "}" << std::endl;
  uk->scale(8.3);
  std::cout << "Scale on 8.3" << std::endl;
  std::cout << "Width of frame = " << uk->getFrameRect().width << std::endl;
  std::cout << "Height of frame = " << uk->getFrameRect().height << std::endl;
  std::cout << "Area of circle = " << uk->getArea() << std::endl;
  return 0;
}
