#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

void OutInf(Shape &object);

void OutInfAboutShape(const Shape &shape)
{
  shape.OutInf();
}


int main()
{
  Rectangle rectangle(10.0, 5.0, {4.0, 3.0});
  std::cout << "  " << std::endl;
  std::cout << "  " << std::endl;
  std::cout << "RECTANGLE: " << std::endl;
  std::cout << "_____________________" << std::endl;
  OutInfAboutShape(rectangle);
  std::cout << "MOVE TO THE POINT" << std::endl;
  rectangle.move({2.55, 3.44});
  OutInfAboutShape(rectangle);
  std::cout << "THE MOVE BY dx OR dy" << std::endl;
  rectangle.move(3.46, 6.57);
  OutInfAboutShape(rectangle);

  Circle circle(10.1, {4.0, 5.3});
  std::cout << "  " << std::endl;
  std::cout << "  " << std::endl;
  std::cout << "CIRCLE: " << std::endl;
  std::cout << "_____________________" << std::endl;
  OutInfAboutShape(circle);
  std::cout << "MOVE TO THE POINT" << std::endl;
  rectangle.move({11.01, 4.37});
  OutInfAboutShape(circle);
  std::cout << "THE MOVE BY dx OR dy" << std::endl;
  rectangle.move(13.36, 7.33);
  OutInfAboutShape(circle);

  Triangle triangle({10.5, 4.7}, {5.3, 7.7}, {8.9, 9.1});
  std::cout << "  " << std::endl;
  std::cout << "  " << std::endl;
  std::cout << " TRIANGLE " << std::endl;
  std::cout << "_____________________ " << std::endl;
  OutInfAboutShape(triangle);
  std::cout << " MOVE TO THE POINT " << std::endl;
  triangle.move({15.01, 9.37});
  OutInfAboutShape(triangle);
  std::cout << " MOVE BY dx OR dy " << std::endl;
  triangle.move(10.36, 9.33);
  OutInfAboutShape(triangle);
  std::cout << "_____________________ " << std::endl;
  return 0;
}
