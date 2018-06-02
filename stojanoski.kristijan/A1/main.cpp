#include <iostream>
#include "rectangle.hpp"
#include "triangle.hpp"
#include "circle.hpp"

void printInfo(const Shape & s)
{
  std::cout << "Area: " << s.getArea() << std::endl;
  rectangle_t fr = s.getFrameRect();
  std::cout << "Frame Rectangle - X: " << fr.pos.x << "  Y: " << fr.pos.y << std::endl;
  std::cout << "Frame Rectangle - Height: " << fr.height << "  Width: " << fr.width << std::endl;
}

int main() 
{
  std::cout << "Creating Rectangle x=20, y=10, w=4, h=6" << std::endl;
  Rectangle r({ 20,10 }, 4, 6);
  printInfo(r);

  std::cout << "Moving Rectangle by dx=7, dy=13" << std::endl;
  r.move(7, 13);
  printInfo(r);

  std::cout << "Moving Rectangle to point x=61.21, y=24.53" << std::endl;
  r.move({ 61.21, 24.53 });
  printInfo(r);

  std::cout << "Creating Triangle with points A(220,39), B(30,15), C(-20,10)" << std::endl;
  Triangle t({ 220,39 }, { 30,15}, { -20,10 });
  printInfo(t);

  std::cout << "Moving Triangle by dx=3, dy=6.1" << std::endl;
  t.move(3, 6.1);
  printInfo(t);

  std::cout << "Moving Triangle to point x=30, y=98" << std::endl;
  t.move({ 30, 98 });
  printInfo(t);

  std::cout << "Creating Circle x=17, y=28, r=6" << std::endl;
  Circle c({ 17,28 }, 6);
  printInfo(c);

  std::cout << "Moving Circle by dx=9.8, dy=18.4" << std::endl;
  c.move(9.8, 18.4);
  printInfo(c);

  std::cout << "Moving Circle to point x=44.11, y=67.2" << std::endl;
  c.move({ 44.11, 67.2 });
  printInfo(c);
  
  return 0;
}
