#include <iostream>
#include <memory>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

int main()
{
  using namespace krasilnikov;

  Rectangle rect (13, 13, {7, 7});
  Circle circ ({7, 7}, 13);
  std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
  std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);

  CompositeShape testComp(rectPtr);
  std::cout << rect.getArea() << std::endl;
  std::cout << testComp.getArea() << std::endl;

  testComp.addShape(circPtr);
  std::cout << circ.getArea() << std::endl;
  std::cout << testComp.getArea() << std::endl;

  testComp.removeShape(0);
  std::cout << circ.getArea() << std::endl;
  std::cout << testComp.getArea() << std::endl;

  testComp.getArea();
  return 0;
}
