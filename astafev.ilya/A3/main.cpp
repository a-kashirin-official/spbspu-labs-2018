#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

int main()
{
  using namespace astafev;
  
  Rectangle rect{ { 30, 30 }, 30, 30 };
  Circle circ{ { 130, 130 }, 30 };

  std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({30, 30}, 30.0, 30.0));
  std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({-1, -1}, 2, 2));
  std::shared_ptr<Shape> circ1 = std::make_shared<Circle>(Circle({130, 130}, 30));

  CompositeShape testComp;
  testComp.addElement(rect1);
  std::cout << rect.getArea() << std::endl;
  std::cout << testComp.getArea() << std::endl;
  
  testComp.addElement(circ1);
  std::cout << rect.getArea()+circ.getArea() << std::endl;
  std::cout << testComp.getArea() << std::endl;
  
  testComp.addElement(rect2);
  testComp.deleteElement(0);
  std::cout << 4+circ.getArea() << std::endl;
  std::cout << testComp.getArea() << std::endl;
  
  testComp.clear();
  
  return 0;
}

