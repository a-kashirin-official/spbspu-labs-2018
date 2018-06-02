#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

void printShapeInfo(const kostylev::Shape & figure)
{
  const kostylev::rectangle_t frame = figure.getFrameRect();
  std::cout << "Area = " << figure.getArea() << std::endl;
  std::cout << "Parameters of frame rectangle for this figure:" << std::endl;
  std::cout << "  Centre: " << "(" << frame.pos.x << ", " << frame.pos.y << ")" << std::endl;
  std::cout << "  Width = " << frame.width << std::endl;
  std::cout << "  Height = " << frame.height << std::endl;
}

int main()
{
  try
  {
    kostylev::Rectangle rectangle{{37.04, 29.45}, 9.67, 5.31};

    std::cout << "Rectangle:" << std::endl;
    printShapeInfo(rectangle);
    rectangle.move({26.05, 19.81});
    printShapeInfo(rectangle);
    rectangle.move(7.19, 1.36);
    printShapeInfo(rectangle);
    rectangle.scale(3.0);
    printShapeInfo(rectangle);

    kostylev::Circle circle{{7.91, 19.42}, 8.34};

    std::cout << "Circle:" << std::endl;
    printShapeInfo(circle);
    circle.move({25.31, 48.07});
    printShapeInfo(circle);
    circle.move(1.15, 2.12);
    printShapeInfo(circle);
    circle.scale(2.5);
    printShapeInfo(circle);
  }
  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}
