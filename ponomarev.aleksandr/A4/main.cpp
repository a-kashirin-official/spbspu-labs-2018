#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix-shape.hpp"

using namespace ponomarev;

int main()
{
  std::shared_ptr<Shape> circle1 = std::make_shared<Circle>(Circle({100.0, 0.0}, 3.0));
  std::shared_ptr<Shape> circle2 = std::make_shared<Circle>(Circle({0.0, 0.0}, 6.0));
  std::shared_ptr<Shape> circle3 = std::make_shared<Circle>(Circle({0.0, 0.0}, 9.0));
  std::shared_ptr<Shape> rec1 = std::make_shared<Rectangle>(Rectangle({0.0, 0.0}, 1.0, 1.0));
  std::shared_ptr<Shape> rec2 = std::make_shared<Rectangle>(Rectangle({0.0, 0.0}, 1.0, 1.0));

  MatrixShape ms;
  ms.addShape(circle1);
  ms.addShape(circle2);
  ms.addShape(circle3);

  std::cout << ms << std::endl;

}

