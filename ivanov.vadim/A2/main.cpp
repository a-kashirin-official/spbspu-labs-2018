#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"

void print(const ivanov::Shape & figure)
{
  ivanov::rectangle_t rect = figure.getFrameRect();
  std::cout << "Area " << figure.getArea() << std::endl;
  std::cout << "Coordinate x: "<< rect.pos.x << " ,coordinate y: " << rect.pos.y<<std::endl;
  std::cout << "Frame rect "<< std::endl;
  std::cout << "Height " << rect.height << std::endl;
  std::cout << "Width " << rect.width << std::endl;
}

int main()
{
  try
  {
    ivanov::point_t rectCentr = {45, 45};
    ivanov::Rectangle rect(rectCentr, 20, 45);

    ivanov::point_t circCentr = {15, 15};
    ivanov::Circle circ(circCentr, 15);

    std::cout << "RECTANGLE" << std::endl;
    print(rect);
    rect.move({ 20, 20 });
    print(rect);
    rect.move(30, 30);
    print(rect);

    std::cout << std::endl;

    std::cout << "CIRCLE" << std::endl;
    print(circ);
    circ.move({ 25, 25 });
    print(circ);
    circ.move(15, 15);
    print(circ);
  }
  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}
