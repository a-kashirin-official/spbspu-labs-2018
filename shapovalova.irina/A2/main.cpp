#include <iostream>
#include <stdexcept>
#include "circle.hpp"
#include "rectangle.hpp"

void print(const shapovalova::Shape & figure)
{
  std::cout << "Area " << figure.getArea() << std::endl;
  std::cout << "Coordinates (x, y): ";
  std::cout << figure.getFrameRect().pos.x << ";" << figure.getFrameRect().pos.y << std::endl;
  std::cout << "Height - " << figure.getFrameRect().height << std::endl;
  std::cout << "Width - " << figure.getFrameRect().width << std::endl;
}

int main()
{
  try
  {
    shapovalova::point_t RectCenter = {50, 20};
    shapovalova::Rectangle r({RectCenter, 30, 40});

    std::cout << "Rectangle: " << std::endl;
    print(r);

    r.move({10, -10});
    std::cout << "-----After moving-----" << std::endl;
    print(r);

    r.scale(2);
    std::cout << "-----After scaling-----" << std::endl;
    print(r);

    shapovalova::point_t CircCenter = {30, 5};
    shapovalova::Circle c(CircCenter, 20);

    std::cout << "Circle: " << std::endl;
    print(c);

    c.move(10, -10);
    std::cout << "-----After moving-----" << std::endl;
    print(c);
  }
  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}
