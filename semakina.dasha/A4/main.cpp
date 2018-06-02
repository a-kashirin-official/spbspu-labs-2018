#include <iostream>
#include <stdexcept>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

using namespace semakina;

namespace semakina
{
  void printInfo(const Shape & shape)
  {
    std::cout << "Center: " << shape.getFrameRect().pos.x << ", " << shape.getFrameRect().pos.y << std::endl;
    std::cout << "Width of frame = " << shape.getFrameRect().width << std::endl;
    std::cout << "Height of frame = " << shape.getFrameRect().height << std::endl;
    std::cout << "Area of rectangle = " << shape.getArea() << std::endl;
  }
}

int main()
{
  try
  {
    Rectangle rect({0, 0}, 5, 10);
    Circle circ({0, 0}, 5);
    std::shared_ptr <Shape> rectPtr = std::make_shared <Rectangle> (rect);
    std::shared_ptr <Shape> circPtr = std::make_shared <Circle> (circ);
    CompositeShape compositeshape(rectPtr);

    std::cout << "CompositeShape = Rectangle" << std::endl;
    printInfo(compositeshape);

    std::cout << "***" << std::endl;

    compositeshape.addShape(circPtr);
    std::cout << "CompositeShape = Rectangle and Circle" << std::endl;
    printInfo(compositeshape);

    std::cout << "Scale(2)" << std::endl;
    compositeshape.scale(2);
    printInfo(compositeshape);

    std::cout << "Move to {60, 60}" << std::endl;
    compositeshape.move({60, 60});
    printInfo(compositeshape);

    std::cout << "Move on {30, 20}" << std::endl;
    compositeshape.move(30, 20);
    printInfo(compositeshape);

    std::cout << "Rotate on 45 degrees" << std::endl;
    compositeshape.rotate(45);
    printInfo(compositeshape);

    std::cout << "***" << std::endl;

    //Matrix
    Matrix matrix(rectPtr);
    std::cout << "Matrix = Rectangle" << std::endl;
    std::cout << "Number of lines = " << matrix.getLine() << std::endl;
    std::cout << "Number of columns = " << matrix.getColumn() << std::endl;

    std::cout << "***" << std::endl;

    matrix.addShape(circPtr);
    std::cout << "Matrix = Rectangle and Circle" << std::endl;
    std::cout << "Number of lines = " << matrix.getLine() << std::endl;
    std::cout << "Number of columns = " << matrix.getColumn() << std::endl;

    std::cout << "***" << std::endl;

    std::cout << "Matrix = 2 Rectangles and 2 Circles" << std::endl;
    Rectangle rect1({60, 70}, 20, 10);
    Circle circ1({60,70}, 10);
    std::shared_ptr <Shape> rectPtr1 = std::make_shared <Rectangle> (rect1);
    std::shared_ptr <Shape> circPtr1 = std::make_shared <Circle> (circ1);
    matrix.addShape(rectPtr1);
    matrix.addShape(circPtr1);
    std::cout << "Number of lines = " << matrix.getLine() << std::endl;
    std::cout << "Number of columns = " << matrix.getColumn() << std::endl;

    if ((matrix[0][0] == rectPtr) && (matrix[0][1] == rectPtr1))
    {
      std::cout << "Rectangles on the first layer" << std::endl;
    }
    if ((matrix[1][0] == circPtr) && (matrix[1][1] == circPtr1))
    {
      std::cout << "Circles on the second layer" << std::endl;
    }
  }
  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  catch (std::out_of_range & error)
  {
    std::cerr << error.what() << std::endl;
    return 2;
  }
  catch (...)
  {
    std::cerr << "Error" << std::endl;
    return 3;
  }
  return 0;
}
