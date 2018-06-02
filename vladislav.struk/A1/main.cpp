#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

void print(const Shape & figure)
{
  std::cout << "Area: " << figure.getArea() << std::endl;
  std::cout << " X: " << figure.getFrameRect().pos.x << " " << " Y: " << figure.getFrameRect().pos.y << std::endl;
  std::cout << " width " << figure.getFrameRect().width << " " << " height " << figure.getFrameRect().height << std::endl;
}

int main()
{
  std::cout << "Creating Rectangle x=30, y=50, width=20, height=20" << std::endl;
  Rectangle rectangle({30.0, 50.0}, 20.0, 20.0);
  print(rectangle);
  std::cout << "Moving Rectangle by dx=5, dy=10" << std::endl;
  rectangle.move(5, 10);
  print(rectangle);

  std::cout << "Moving Rectangle to point x=35.41, y=17.41" << std::endl;
  rectangle.move({35.41, 17.41});
  print(rectangle);

  std::cout << "Creating Circle x=11.0, y=15.0, r=3.0" << std::endl;
  Circle circle({11.0, 15.0}, 3.0);
  print(circle);

  std::cout << "Moving Circle by dx=5, dy=8" << std::endl;
  circle.move(5, 8);
  print(circle);

  std::cout << "Moving Circle to point x=10.22, y=8.52" << std::endl;
  circle.move({10.22, 8.51});
  print(circle);
  return 0;
}

