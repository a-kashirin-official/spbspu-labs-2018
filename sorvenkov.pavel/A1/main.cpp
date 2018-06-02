#include <iostream>

#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

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
  Rectangle rect(10.0, 5.0, {4.0, 3.0});
  std::cout << "RECTANGLE: " << std::endl;
  outInf(rect);
  std::cout << "MOVE TO THE POINT" << std::endl;
  rect.move({2.28, 3.55});
  outInf(rect);
  std::cout << "THE MOVE BY dx OR dy" << std::endl;
  rect.move(3.22, 6.11);
  outInf(rect);

  Circle circ(10.1, {4.0, 5.3});
  std::cout << "_____________________" << std::endl
  << "CIRCLE: " << std::endl;
  outInf(circ);
  std::cout << "MOVE TO THE POINT" << std::endl;
  circ.move({12.55, 3.21});
  outInf(circ);
  std::cout << "THE MOVE BY dx OR dy" << std::endl;
  circ.move(13.36, 7.33);
  outInf(circ);

  Triangle tri({ -8.0, -3.0 }, { 4.0, -12.0 }, { 8.0, 10.0 });
  std::cout << "_____________________" << std::endl
  << "TRIANGLE: " << std::endl;
  outInf(tri);
  std::cout << "MOVE TO THE POINT" << std::endl;
  tri.move({15.01, 9.37});
  outInf(tri);
  std::cout << "THE MOVE BY dx OR dy" << std::endl;
  tri.move(10.36, 9.33);
  outInf(tri);
  
  return 0;
}
