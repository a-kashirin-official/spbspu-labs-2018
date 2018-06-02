#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

using namespace kramarov;

void printProperties(Shape & figure)
{
  std::cout << "Area = " << figure.getArea() << std::endl;
  std::cout << "Frame Rectangle center on x-axis" << figure.getFrameRect().pos.x << std::endl;
  std::cout << "Frame Rectangle center on y-axis" << figure.getFrameRect().pos.y << std::endl;
  std::cout << "Height of Frame Rectangle = " << figure.getFrameRect().height << std::endl;
  std::cout << "Width of Frame Rectangle = " << figure.getFrameRect().width << std::endl;
}

int main()
{
  try
  {
    Rectangle rectangle(1.5, 2.0, {10.0, 10.0});
    std::cout << "Base rectangle's properties:" <<std::endl;
    printProperties(rectangle);
    rectangle.move(10.0, 1.5);
    std::cout << "Rectangle's properties after moving by shift:" <<std::endl;
    printProperties(rectangle);
    rectangle.move({11.09, 26.04});
    std::cout << "Rectangle's properties after reinitalizing center:" <<std::endl;
    printProperties(rectangle);
    rectangle.scale(2.0);
    std::cout << "Rectangle's properties after scaling:" <<std::endl;
    printProperties(rectangle);

    Circle circle({50.0, 30.0}, 20.0);
    std::cout << "Base circle's properties:" <<std::endl;
    printProperties(circle);
    circle.move(15.0, 2.6);
    std::cout << "Circle's properties after moving by shift:" <<std::endl;
    printProperties(circle);
    circle.move({3.14, 2.7});
    std::cout << "Circle's properties after reinitalizing center:" <<std::endl;
    printProperties(circle);
    circle.scale(2.0);
    std::cout << "Circle's properties after scaling:" <<std::endl;
    printProperties(circle);
    
    CompositeShape composition(&circle);
    std::cout << "Base composition's properties:" <<std::endl;
    printProperties(composition);
    std::cout << "(must be same with this)" <<std::endl;
    printProperties(circle);
    composition.addShape(&rectangle);
    std::cout << "Composition's properties after rectangle addition:" <<std::endl;
    printProperties(composition);
    composition.deleteShape(0);
    std::cout << "Composition's properties after circle deletion:" <<std::endl;
    printProperties(composition);
    std::cout << "(must be same with this)" <<std::endl;
    printProperties(rectangle);
  }
  catch (std::invalid_argument & ia)
  {
    std::cerr << ia.what() << std::endl;
    return 1;
  }
  return 0;
}
