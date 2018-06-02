#include <iostream>
#include <cmath>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix-shape.hpp"

using namespace babintseva;

int main()
{
  auto cir = std::make_shared<Circle>(point_t{0,0},3);
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

  auto rect1 = std::make_shared<Rectangle>(point_t{0,4},10,20);
  std::cout << "\t FRAME RECTANGLE: " << "\n";
  std::cout << "Coordinates - (" << rect1->getPos().x
            << ", " << rect1->getPos().y << ")\n"
            << "Parameters of frame rectangle:\n"
            << "Width - " << rect1->getFrameRect().width << "\n"
            << "Height - " << rect1->getFrameRect().height << "\n"
            << "Area - " << rect1->getArea() << "\n";
  rect1->move({5, -30});
  rect1->move(3, -4);
  std::cout << "Move to point (5,-30) and move on (3,-4)\n";
  std::cout << "Coordinates: (" << rect1->getPos().x << ","
            << rect1->getPos().y << ")\n";
  rect1->scale(5);
  std::cout << "Scaling with ratio = 5\n";
  std::cout << "Width of frame rectangle:" << rect1->getFrameRect().width << "\n"
            << "Height of frame rectangle:" << rect1->getFrameRect().height << "\n";

  auto rect2 = std::make_shared<Rectangle>(point_t{0,4},10,20);

  MatrixShape matrixShape(rect1);
  std::cout << "Matrix was created\n";

  matrixShape.addShape(cir);
  matrixShape.addShape(rect2);

  matrixShape.print();
}