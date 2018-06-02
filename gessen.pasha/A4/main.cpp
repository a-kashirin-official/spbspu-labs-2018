#include "circle.hpp"
#include "matrix.hpp"
#include "rectangle.hpp"
#include <cmath>
#include <iostream>

using namespace gessen;

int main()
{
  Rectangle *rect = new Rectangle({128.0, 256.0}, 14.0, 57.0);
  rect->printShapeName();
  std::cout << "after rotating" << std::endl;
  rect->rotate(90);
  rect->printShapeName();
  Circle *circ = new Circle ({59.0, 61.0}, 10.0);
  circ->printShapeName();
  std::cout << "after rotating" << std::endl;
  circ->rotate(90);
  circ->printShapeName();
  try
  {
    Matrix();
    Matrix mtrx(rect);
    mtrx.addShape(circ);
    mtrx.printShapes();
  }
  catch (std::invalid_argument &ex)
  {
    std::cerr << ex.what() << std::endl;
    return 1;
  }
  catch (...) {
    std::cerr << "Error" << std::endl;
    return 2;
  }
  return 0;
}
