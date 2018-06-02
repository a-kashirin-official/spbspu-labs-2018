#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

void testShape(Shape & shapeObject) {
  std::cout << "Initial values:" << std::endl << "Area: " << shapeObject.getArea() << std::endl;
  shapeObject.getFrameRect();

  std::cout << "After moving in (2.0, 5.0):" << std::endl;
  shapeObject.move(2.0, 5.0);
  std::cout << "Area: " << shapeObject.getArea() << std::endl;
  shapeObject.getFrameRect();
  
  std::cout << "After moving to ({50, 100}):" << std:: endl;
  shapeObject.move({50, 100});
  std::cout << "Area: " << shapeObject.getArea() << std::endl << std::endl;
  shapeObject.getFrameRect();
}

int main() {
  try {
    Circle circleObject({30, 30}, 10);
    Rectangle rectangleObject({30, 30}, 10, 20);
    Triangle triangleObject({0, 0}, {90, 0}, {0, 30});

    testShape(rectangleObject);
    testShape(circleObject);
    testShape(triangleObject);
  }
  catch(std::invalid_argument & invArg) {
    std::cerr << invArg.what() << std::endl;
    return 1;
  }
  return 0;
}
