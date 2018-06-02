#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

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
  try
  {
    Circle circ(circCenter, 10);

    std::cout << "CIRCLE" << std::endl;
    print(circ);
    circ.move({ 25, 25 });
    print(circ);
    circ.move(15, 15);
    print(circ);
  }
  catch(IncorrectDataException)
  {
    std::cout << "INCORRECT RADIUS" << std::endl;
  }

  std::cout << std::endl;

  point_t rectCenter = { 50, 50 };

  try
  {
    Rectangle rect(rectCenter, -20, -50);
    std::cout << "RECTANGLE" << std::endl;
    print(rect);
    rect.move({ 20, 20 });
    print(rect);
    rect.move(30, 30);
    print(rect);
  }
  catch(IncorrectDataException)
  {
    std::cout << "INCORRECT HEIGHT OR WIDTH" << std::endl;
  }
}
