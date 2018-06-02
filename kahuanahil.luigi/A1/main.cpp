#include "circle.hpp"
#include "rectangle.hpp"
#include <iostream>

int main()
{
  double x = 5.0, y = 10;
  point_t pos{ 7.5, 6.2 };
  Rectangle rect = { 10.5, 12.3, pos };
  Circle cir = { 2.3, pos};
  Shape *po = &rect;
  
  std::cout << "-----------------------" << std::endl;
  std::cout << "Rectangle :" << std::endl;
  std::cout << "Center (" << po->getCenter().x << ";" << po->getCenter().y << ")" << std::endl;
  std::cout << "Area = " << po->getArea() << std::endl;
  std::cout << "Height= " << po->getFrameRect().height << "; Width= " << po->getFrameRect().width << std::endl;
  std::cout << "Center of FrameRectangle (" << po->getFrameRect().pos.x << ";" << po->getFrameRect().pos.y << ")" << std::endl;
  pos = { 4.6, 3.2 };
  std::cout << "Coordinates (" << po->getCenter().x << ";" << po->getCenter().y << ")" << std::endl;
  po->move(pos);
  std::cout << "Center after movement (" << po->getCenter().x << ";" << po->getCenter().y << ")" << std::endl;
  po->move(x, y);
  std::cout << "Center after OX moving (" << po->getCenter().x << ";" << po->getCenter().y << ")" << std::endl;
  std::cout << "-------------------------" << std::endl;
  pos = { 3.5, 4.3 };
  Shape *poi = &cir;
  std::cout << "-------------------------------" << std::endl;
  std::cout << "Circle :" << std::endl;
  std::cout << "Center (" << poi->getCenter().x << ";" << poi->getCenter().y << ")" << std::endl;
  std::cout << "Area =" << poi->getArea() << std::endl;
  std::cout << "Center of FrameRectangle (" << poi->getFrameRect().pos.x << ";" << poi->getFrameRect().pos.y << ")" << std::endl;
  pos = { 2.7, 3.2 };
  std::cout << "Coordinates of point (" << poi->getFrameRect().pos.x << ":" << poi->getFrameRect().pos.y << ")" << std::endl;
  poi->move(pos);
  std::cout << "Center after movement (" << poi->getCenter().x << ";" << poi->getCenter().y << ")" << std::endl;
  poi->move(x, y);
  std::cout << "Center after OX moving (" << poi->getCenter().x << ";" << poi->getCenter().y << ")" << std::endl;
  std::cout << "-------------------------------" << std::endl;
  
  return 0;
}
