#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"


int main()
{
  try
  {
    Circle circleObject({0.0, 0.0}, 10.0);
      std::cout << "--CIRCLE--" << std::endl;
      std::cout << "Circle area - " << circleObject.getArea() << std::endl;
      std::cout << "Point: "  ;
      std::cout << "Ox - "<< circleObject.getFrameRect().pos.x << " ";
      std::cout << "Oy - "<< circleObject.getFrameRect().pos.y << std::endl;
      circleObject.move(4.0,4.0);
      std::cout << "Move to new point: "  ;
      std::cout << "Ox - "<< circleObject.getFrameRect().pos.x << " ";
      std::cout << "Oy - "<< circleObject.getFrameRect().pos.y << std::endl;
      std::cout << "After moving" << std::endl;
      std::cout << "Circle area - " << circleObject.getArea() << std::endl;
      std::cout << "New point: "  ;
      std::cout << "Ox - "<< circleObject.getFrameRect().pos.x << " ";
      std::cout << "Oy - "<< circleObject.getFrameRect().pos.y << std::endl << std::endl;
      
    Rectangle rectangleObject({0.0, 0.0}, 2.5, 2.5);
      std::cout << "--RECTANGLE--" << std::endl;
      std::cout << "Rectangle area - " << rectangleObject.getArea() << std::endl;
      std::cout << "Point: "  ;
      std::cout << "Ox - "<< rectangleObject.getFrameRect().pos.x << " ";
      std::cout << "Oy - "<< rectangleObject.getFrameRect().pos.y << std::endl;
      rectangleObject.move(8.0,8.0);
      std::cout << "Move to new point: "  ;
      std::cout << "Ox - "<< rectangleObject.getFrameRect().pos.x << " ";
      std::cout << "Oy - "<< rectangleObject.getFrameRect().pos.y << std::endl;
      std::cout << "After moving" << std::endl;
      std::cout << "Rectangle area - " << rectangleObject.getArea() << std::endl;
      std::cout << "New point: "  ;
      std::cout << "Ox - "<< rectangleObject.getFrameRect().pos.x << " ";
      std::cout << "Oy - "<< rectangleObject.getFrameRect().pos.y << std::endl << std::endl;
      
    Triangle triangleObject({0.0, 0.0}, {10.0, 10.0}, {10.0, 0.0});
      std::cout << "--TRIANGLE--" << std::endl;
      std::cout << "Triangle area - " << triangleObject.getArea() << std::endl;
      std::cout << "Point: "  ;
      std::cout << "Ox - "<< triangleObject.getFrameRect().pos.x << " ";
      std::cout << "Oy - "<< triangleObject.getFrameRect().pos.y << std::endl;
      triangleObject.move(8.0,8.0);
      std::cout << "Move to new point: "  ;
      std::cout << "Ox - "<< triangleObject.getFrameRect().pos.x << " ";
      std::cout << "Oy - "<< triangleObject.getFrameRect().pos.y << std::endl;
      std::cout << "After moving" << std::endl;
      std::cout << "Triangle area - " << triangleObject.getArea() << std::endl;
      std::cout << "New point: "  ;
      std::cout << "Ox - "<< triangleObject.getFrameRect().pos.x << " ";
      std::cout << "Oy - "<< triangleObject.getFrameRect().pos.y << std::endl << std::endl;

  }
  catch(std::invalid_argument & invArg)
  {
    std::cerr << invArg.what() << std::endl;
    return 1;
  }
  return 0;
}
