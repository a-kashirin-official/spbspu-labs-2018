#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

using namespace mihajlov;

int main()
{
  try
  {
    std::shared_ptr<mihajlov::Shape> rectangle1(new mihajlov::Rectangle({10.0, 10.0}, 4.0, 5.0));
    std::shared_ptr<mihajlov::Shape> rectangle2(new mihajlov::Rectangle({0.0, 0.0}, 6.0, 4.0));
    std::shared_ptr<mihajlov::Shape> circle(new mihajlov::Circle({0.0}, 5));
    std::shared_ptr<mihajlov::CompositeShape> composite(new mihajlov::CompositeShape(rectangle1));
    composite->addShape(circle);


    rectangle1->getInfo();
    std::cout << std::endl;
    rectangle1->rotate(90);
    std::cout << "Rotared rectangle by 90 degrees: " << std::endl;
    rectangle1->getInfo();
    rectangle1->rotate(20);
    std::cout << "Rotated rectangle by 20 degrees: " << std::endl;
    rectangle1->getInfo();
    std::cout << std::endl;

    std::cout << std::endl;
    circle->getInfo();
    circle->rotate(100);
    std::cout << "Rotated circle by 100 degrees (nothing happened) : " << std::endl;
    circle->getInfo();
    std::cout << std::endl;

    composite->getInfo();
    (*composite)[0].getInfo();
    (*composite)[1].getInfo();
    composite->rotate(31);
    std::cout << "Rotated composite-shape by 31 degrees :" << std::endl;
    composite->getInfo();
    std::cout << std::endl;
    (*composite)[0].getInfo();
    (*composite)[1].getInfo();
    std::cout << std::endl;

    mihajlov::Matrix matrix;
    std::cout << "Rows: " << matrix.getLayersCount() << " " << "Columns: " << matrix.getLayerSize() << std::endl;
    matrix.addShape(rectangle1);
    std::cout << "Rows: " << matrix.getLayersCount() << " " << "Columns: " << matrix.getLayerSize() << std::endl;
    matrix.addShape(rectangle2);
    std::cout << "Rows: " << matrix.getLayersCount() << " " << "Columns: " << matrix.getLayerSize() << std::endl;
    matrix.addShape(circle);
    std::cout << "Rows: " << matrix.getLayersCount() << " " << "Columns: " << matrix.getLayerSize() << std::endl;
    matrix.addShape(composite);
    std::cout << "Rows: " << matrix.getLayersCount() << " " << "Columns: " << matrix.getLayerSize() << std::endl;
    matrix.view();
  }
  catch (std::invalid_argument& e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }


  return 0;
}
