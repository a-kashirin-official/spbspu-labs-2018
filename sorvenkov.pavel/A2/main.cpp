#include <iostream>

#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

using namespace sorvenkov;

void outInf(Shape& shp)
{
  std::cout << "Width:  " << shp.getFrameRect().width << std::endl
  << "Height: " << shp.getFrameRect().height << std::endl
  << "Area:   " << shp.getArea() << std::endl
  << "Pos(x): " << shp.getFrameRect().pos.x << std::endl
  << "Pos(y): " << shp.getFrameRect().pos.y << std::endl
  << "_____________________ " << std::endl;
}

int main() 
{
  try
  {
    sorvenkov::Rectangle rect(4.0, 5.0, {2.0, 3.0});
    outInf(rect);
    sorvenkov::Circle circ(4.0, {2.0, 3.0});
    outInf(circ);
    sorvenkov::Triangle tri({0.0, 0.0}, {2.0, 4.0}, {4.0, 0.0});

    rect.move(3.0, 9.0);
    circ.move(5.0, 7.0);
    circ.move(4.0, 6.0);

    std::cout << "After first move:" << std::endl;
    outInf(rect);
    outInf(circ);
    outInf(tri);

    circ.move({10.0, 10.0});
    rect.move({20.0, 20.0});
    tri.move({30.0, 30.0});
    std::cout << "After second move:" << std::endl;
    outInf(rect);
    outInf(circ);
    outInf(tri);

    circ.scale(2.0);
    rect.scale(2.0);
    tri.scale(2.0);
    std::cout<<"After scaling:"<<std::endl;
    outInf(rect);
    outInf(circ);
    outInf(tri);

  } 
  catch (std::invalid_argument & error) 
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}
