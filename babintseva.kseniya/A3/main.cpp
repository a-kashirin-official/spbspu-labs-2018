#include <iostream>
#include "memory"
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
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

  auto rect = std::make_shared<Rectangle>(point_t{0,4},10,20);
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

  CompositeShape compositeShape(cir);
  compositeShape.addShape(rect);

  std::cout << "-------------------------\n";
  std::cout << "Coordinates: (" << compositeShape.getFrameRect().pos.x << ", "
            << compositeShape.getFrameRect().pos.y << ")\n"
            << "Width - " << compositeShape.getFrameRect().width << "\n"
            << "Height - " << compositeShape.getFrameRect().height << "\n"
            << "Area - " << compositeShape.getArea() << "\n";
  compositeShape.move({10, 20});
  compositeShape.move(5, 5);
  std::cout << "Move to point (10, 20) and move on (5, 5)\n";
  std::cout << "Coordinates: (" << compositeShape.getPos().x << ","
            << compositeShape.getPos().y << ")\n";
  compositeShape.scale(5);
  std::cout << "Scaling with ratio = 5\n";
  std::cout << "Width of frame rectangle:" << compositeShape.getFrameRect().width << "\n"
            << "Height of frame rectangle:" << compositeShape.getFrameRect().height << "\n";

  return 0;
}
