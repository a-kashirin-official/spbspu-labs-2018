#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

#include "cmath"
#include <iostream>

int main()
{
  std::cout << "Testing of CompositeShape" << std::endl;
  std::shared_ptr<marchenko::Shape> testRect =
    std::make_shared<marchenko::Rectangle>(marchenko::Rectangle(5.0, 15.0, {35.0, 35.0}));
  std::shared_ptr<marchenko::Shape> testCirc =
    std::make_shared<marchenko::Circle>(marchenko::Circle({3.0, 2.5}, 105));
  marchenko::CompositeShape testComp(testRect);
  testComp.addShape(testCirc);
  std::cout << "Parameters of Composite Shape: " << std::endl;
  std::cout << testComp.getSize() << " parts here" << std::endl;
  std::cout << "Area of this big figure: " << testComp.getArea() << std::endl;
  std::cout << "Parameters of FrameRect: height = " << testComp.getFrameRect().height
    << " width = " << testComp.getFrameRect().width << std::endl;
  std::cout << "Now we will change our shape"<<std::endl;
  std::cout << "New position of center is {25.0,100.0}"<< std::endl;
  testComp.move({25.0,100.0});
  std::cout << "Upd position is {30.0,105.0}"<< std::endl;
  testComp.move(5.0,5.0);
  std::cout << "Shape is scaled with koef=5.0"<< std::endl;
  testComp.scale(5.0);
  testComp.deleteShape(0);
  std::cout << "After upd " << testComp.getSize() << " parts here" << std::endl;
  return 0;
}
