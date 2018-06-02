#include "circle.hpp"
#include "rectangle.hpp"
#include <iostream>

using namespace lashchenov;

void printInfoAboutShape(const Shape & shape)
{
  shape.printInfo();
}

int main()
{
  try {
    Circle circle(5, {1, 0});
    Rectangle rectangle(5, 6, 1, 0);

    printInfoAboutShape(circle);
    printInfoAboutShape(rectangle);

    circle.move({1, 2});
    circle.scale(1.5);
    printInfoAboutShape(circle);

    std::cout << "Area is " << circle.getArea() << std::endl;
  }
  catch (std::exception & error) {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}
