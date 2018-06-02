#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
using namespace babintseva;

int main()
{
  Circle figure1({0,0},3);
  Shape *cir = &figure1;
  std::cout << "\t CIRCLE: " << "\n";
  std::cout << "Coordinates - (" << cir->getPos().x
            << ", " << cir->getPos().y << ")\n"
            << "Rectangle around circle:\n"
            << "Width - " << cir->getFrameRect().width << "\n"
            << "Height - " << cir->getFrameRect().height << "\n"
            << "Area - " << cir->getArea() << "\n";
  cir->move({5, -5});
  cir->move(13, 10);
  std::cout << "Move to point (5,-5) and move on (13,10)\n";
  std::cout << "Coordinates: (" << cir->getPos().x << ","
            << cir->getPos().y << ")\n";
  cir->scale(5);
  std::cout << "Scaling with ratio = 5\n";
  std::cout << "Width of frame rectangle:" << cir->getFrameRect().width << "\n"
            << "Height of frame rectangle:" << cir->getFrameRect().height << "\n";

  Rectangle figure2({0,4},10,20);
  Shape *rect = &figure2;
  std::cout << "\t FRAME RECTANGLE: " << "\n";
  std::cout << "Coordinates - (" << rect->getPos().x
            << ", " << rect->getPos().y << ")\n"
            << "Parameters of frame rectangle:\n"
            << "Width - " << rect->getFrameRect().width << "\n"
            << "Height - " << rect->getFrameRect().height << "\n"
            << "Area - " << rect->getArea() << "\n";
  rect->move({5, -30});
  rect->move(3, -4);
  std::cout << "Move to point (5,-30) and move on (3,-4)\n";
  std::cout << "Coordinates: (" << rect->getPos().x << ","
            << rect->getPos().y << ")\n";
  rect->scale(5);
  std::cout << "Scaling with ratio = 5\n";
  std::cout << "Width of frame rectangle:" << rect->getFrameRect().width << "\n"
            << "Height of frame rectangle:" << rect->getFrameRect().height << "\n";

  return 0;
}
