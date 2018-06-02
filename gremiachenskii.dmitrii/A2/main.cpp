#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
using namespace std;
using namespace gremiachenskii;

void print(const Shape & figure)
{
  rectangle_t rect = figure.getFrameRect();
  std::cout << "AREA: " << figure.getArea() << std::endl;
  std::cout << "COORDINATES: (" << rect.pos.x << ", " << rect.pos.y << ")" << std::endl;
  std::cout << "FRAME RECT: " << std::endl
            << "* Height: " << rect.height << std::endl
            << "* Width: " << rect.width << std::endl;
}

int main()
{
  point_t circCenter = { 10, 10 };
  std::cout << "CIRCLE" << std::endl;
  try
  {
    Circle circ(circCenter, 10);
    print(circ);
    circ.move({ 25, 25 });
    print(circ);
    circ.move(15, 15);
    print(circ);
    circ.scale(15);
    print(circ);
  }
  catch(std::invalid_argument & except)
  {
    std::cerr << except.what() << std::endl;
  }

  std::cout << std::endl;

  point_t rectCenter = { 50, 50 };
  std::cout << "RECTANGLE" << std::endl;
  try
  {
    Rectangle rect(rectCenter, 20, 50);
    print(rect);
    rect.move({ 20, 20 });
    print(rect);
    rect.move(30, 30);
    print(rect);
    rect.scale(20);
    print(rect);
  }
  catch(std::invalid_argument & except)
  {
    std::cerr << except.what() << std::endl;
  }

  return 0;
}
