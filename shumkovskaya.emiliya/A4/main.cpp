#include <iostream>
#include <memory>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

using namespace shumkovskaya;

void printInfo(const shumkovskaya::Shape & object)
{
  std::cout << "Area: " << object.getArea() << std::endl;
  const shumkovskaya::rectangle_t frame = object.getFrameRect();
  std::cout << "Frame rectangle of object:" << std::endl;
  std::cout << "Width: " << frame.width << std::endl;
  std::cout << "Height: " << frame.height << std::endl;
  std::cout << "Center: " << frame.pos.x << ", " << frame.pos.y << std::endl;
}

int main()
{
  try
  {
    shumkovskaya::Rectangle rect(2.0, 1.0, { 1.0, 0.5 });
    std::cout << "Rectangle" << std::endl;
    printInfo(rect);
    shumkovskaya::Circle cir(1.0, { 5.0, 3.0 });
    std::cout << "Circle" << std::endl;
    printInfo(cir);
    std::shared_ptr <shumkovskaya::Shape> rectanglePtr =
      std::make_shared <shumkovskaya::Rectangle>(rect);
    std::shared_ptr <shumkovskaya::Shape> circlePtr =
      std::make_shared <shumkovskaya::Circle>(cir);
    std::cout << "Create composite shape" << std::endl;
    shumkovskaya::CompositeShape shapes(rectanglePtr);
    printInfo(shapes);
    std::cout << "Amount of shapes = " << shapes.getAmount() << std::endl;
    std::cout << "Add circle" << std::endl;
    shapes.addShape(circlePtr);
    printInfo(shapes);
    std::cout << "Amount of shapes = " << shapes.getAmount() << std::endl;
    shapes.scale(2.0);
    std::cout << "Composite shape after scaling on 2:" << std::endl;
    printInfo(shapes);
    std::cout << "Amount of shapes = " << shapes.getAmount() << std::endl;
    shapes.move({ 0.0, 0.0 });
    std::cout << "Composite shape after moving" << std::endl;
    printInfo(shapes);
    std::cout << "Amount of shapes = " << shapes.getAmount() << std::endl;
    rect.rotate(180);
    std::cout << "Rectangle after rotating on 180 degrees" << std::endl;
    printInfo(rect);
    cir.rotate(46);
    std::cout << "Circle after rotating on 46 degrees" << std::endl;
    printInfo(cir);
    shapes.rotate(90);
    std::cout << "Composite shape after rotating on 90 degrees" << std::endl;
    printInfo(shapes);
    shapes.removeAll();
    shumkovskaya::Circle circleM{2.0 ,{ -2.0, -2.0 } };
    shumkovskaya::Rectangle rectangleM1{ 2.0, 2.0 ,{ -2.0, 0.0 } };
    shumkovskaya::Rectangle rectangleM2{ 6.0, 3.0,{ 1.0, 1.0 } };
    shumkovskaya::Rectangle rectangleM3{ 2.0, 4.0, { 3.0, 1.0 } };
    shumkovskaya::Rectangle rectangleM4{ 4.0, 4.0,{ 3.0, 3.0 } };
    std::shared_ptr< shumkovskaya::Shape > circlePtrM = std::make_shared<shumkovskaya::Circle >(circleM);
    std::shared_ptr< shumkovskaya::Shape > rectanglePtrM1 = std::make_shared<shumkovskaya::Rectangle >(rectangleM1);
    std::shared_ptr< shumkovskaya::Shape > rectanglePtrM2 = std::make_shared<shumkovskaya::Rectangle >(rectangleM2);
    std::shared_ptr< shumkovskaya::Shape > rectanglePtrM3 = std::make_shared<shumkovskaya::Rectangle >(rectangleM3);
    std::shared_ptr< shumkovskaya::Shape > rectanglePtrM4 = std::make_shared<shumkovskaya::Rectangle >(rectangleM4);
    shumkovskaya::CompositeShape shapes2(circlePtrM);
    shapes2.addShape(rectanglePtrM1);
    shapes2.addShape(rectanglePtrM2);
    shapes2.addShape(rectanglePtrM3);
    shapes2.addShape(rectanglePtrM4);
    shumkovskaya::Matrix matrix(shapes2);
    std::cout << "Matrix:" << std::endl;
    std::cout << "Amount of layers: " << matrix.getAmount() << std::endl;
    std::cout << "Size of layers: " << matrix.getSize() << std::endl;
    if (matrix[0][0] == circlePtrM)
    {
      std::cout << " element in first layer is circle" << std::endl;
    }
    if (matrix[0][1] == rectanglePtrM3)
    {
      std::cout << " element in first layer is rectangle 3" << std::endl;
    }
    if (matrix[1][0] == rectanglePtrM1)
    {
      std::cout << "element in second layer is rectangle 1" << std::endl;
    }
    if (matrix[1][1] == rectanglePtrM4)
    {
      std::cout << "element in second layer is rectangle 4" << std::endl;
    }
    if (matrix[2][0] == rectanglePtrM2)
    {
      std::cout << "element in third layer is rectangle 2" << std::endl;
    }
    if (matrix[2][1] == nullptr)
    {
      std::cout << "element in third layer is nullptr" << std::endl;
    }
  }
  catch (std::invalid_argument & e)
  {
    std::cerr << e.what() << std::endl;
  }
  catch (std::out_of_range & e)
  {
    std::cerr << e.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "Exception occured" << std::endl;
  }
  return 0;
}
