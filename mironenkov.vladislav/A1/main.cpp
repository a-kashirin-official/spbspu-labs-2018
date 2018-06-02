#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

void testShape(Shape & shapeObject)
{
  std::cout << "Start parameters:" << std::endl;
  std::cout << "Area: " << shapeObject.getArea() << std::endl;
  shapeObject.getFrameRect();

  std::cout << "After moving in (3.0, 3.0)" << std::endl;
  shapeObject.move(3.0, 3.0);
  std::cout << "Area: " << shapeObject.getArea() << std::endl;
  shapeObject.getFrameRect();
  
  std::cout << "After moving to ({100, 100})" << std:: endl;
  shapeObject.move({100, 100});
  std::cout << "Area: " << shapeObject.getArea() << std::endl << std::endl;
  shapeObject.getFrameRect();
}

int main()
{
  try
  {
    Circle circleObject({30, 30}, 10);
    Rectangle rectangleObject({30, 30}, 10, 20);
    Triangle triangleObject({0, 0}, {90, 0}, {0, 30});

    testShape(circleObject);
    testShape(rectangleObject);
    testShape(triangleObject);
  }
  catch(std::invalid_argument & invArg) 
  {
    std::cerr << invArg.what() << std::endl;
    return 1;
  }
  return 0;
}
