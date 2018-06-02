#include <iostream>
#include <cmath>
#include "circle.hpp"
#include "rectangle.hpp"
#include "matrix.hpp"
#include "composite-shape.hpp"

using namespace revtova;

void printInfo(const Shape &figure)
{
  std::cout << "Area: " << figure.getArea() << std::endl;
  const rectangle_t frame = figure.getFrameRect();
  std::cout << "Frame for figure:" << std::endl;
  std::cout << "\tCentre of frame: " << frame.pos.x << ", " << frame.pos.y << std::endl;
  std::cout << "\tWidth of frame: " << frame.width << std::endl;
  std::cout << "\tHeight of frame: " << frame.height << std::endl;
}

int main()
{
  Circle circ({ 2.0, 2.0 },1.0);
  std::shared_ptr<Shape> circPtr = std::make_shared<Circle>(circ);
  CompositeShape CompShp(circPtr);
  Rectangle rect({ 2.0, 4.0 }, 4.0, 6.0);
  std::shared_ptr<Shape> rectPtr = std::make_shared<Rectangle>(rect);
  CompShp.addShape(rectPtr);
  Rectangle rect1 ({1.0, 5.0}, 3.0, 7.0);
  std::shared_ptr<Shape> rect1Ptr = std::make_shared<Rectangle>(rect1);
  CompShp.addShape(rect1Ptr);
  std::cout << "Composite shape:" << std::endl;
  printInfo(CompShp);
  CompShp.rotate(90);
  printInfo(CompShp);
  CompShp.scale(2.0);
  printInfo(CompShp);
  CompShp.remove(2);
  printInfo(CompShp);
  std::cout << std::endl;
  try
  {
    Matrix matrix(rectPtr);
    matrix.addShape(circPtr);
    matrix.addShape(rect1Ptr);
    matrix.print();
  }
  catch (std::invalid_argument & e)
  {
    std::cerr << e.what() << std::endl;
  }
  catch (std::out_of_range & e)
  {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
