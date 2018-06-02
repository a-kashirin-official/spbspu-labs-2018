#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  Circle figure1({0,0},3);
  Shape *cir = &figure1;
  std::cout << "\t CIRCLE: " << "\n";
  cir->printInformation();
  std::cout << "Rectangle around circle:\n";
  std::cout << "Width - " << cir->getFrameRect().width << "\n"
            << "Height - " << cir->getFrameRect().height << "\n"
            << "Area of circle - " << cir->getArea() << "\n";
  cir->move({5,-5});
  cir->move(13,10);
  std::cout << "Move to point (5,-5) and move on (13,10)\n";
  cir->printInformation();

  Rectangle figure2({0,4},10,20);
  Shape *rect = &figure2;
  std::cout << "\t FRAME RECTANGLE: " << "\n";
  rect->printInformation();
  std::cout << "Width - " << rect->getFrameRect().width << "\n"
            << "Height - " << rect->getFrameRect().height << "\n"
            << "Area of rectangle - " << rect->getArea() << "\n";
  rect->move({5,-30});
  rect->move(3,-4);
  std::cout << "Move to point (5,-30) and move on (3,-4)\n";
  rect->printInformation();

  return 0;
}

