#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "cmath"


int main()
{
  try
  {
    shalgueva::point_t point = {30.0, 130.0};

    shalgueva::Rectangle r({30.0, 70.0, point});
    shalgueva::Shape *rectangle = & r;
    std::cout << "Area of rectangle " << rectangle -> getArea() << std::endl;
    rectangle -> getFrameRect();
    rectangle -> move(70.0, -30.0);
    std::cout << "After moving" << std::endl;
    rectangle -> scale(2.0);
    std::cout << "Area of rectangle " << rectangle -> getArea() << std::endl;
    rectangle -> getFrameRect();

    shalgueva::Circle c({200.0, 130.0}, 25.0);
    shalgueva::Shape *circle = & c;
    std::cout << "Area of circle " << circle -> getArea() << std::endl;
    circle -> getFrameRect();
    circle -> move({10.0, 10.0});
    std::cout << "After moving" <<std::endl;
    circle -> scale(0.9);
    std::cout << "Area of circle " << circle -> getArea() << std::endl;
    circle -> getFrameRect();


    std::cout << "[CompositeShape]" << std::endl;
    std::shared_ptr<shalgueva::Shape> rect1 =
      std::make_shared<shalgueva::Rectangle>(shalgueva::Rectangle({10.0, 10.0, {25.0, 25.0}}));
    std::shared_ptr<shalgueva::Shape> circ1 =
      std::make_shared<shalgueva::Circle>(shalgueva::Circle({50.0, 50.0}, 10));
    shalgueva::CompositeShape testComp(rect1);
    testComp.addShape(circ1);
    std::cout << "From Composite Shape1: " << std::endl;
    std::cout << testComp.getLength() << " Figures here" << std::endl;
    std::cout << "testComp getArea: " << testComp.getArea() << std::endl;
    std::cout << "testComp getFrameRect: height = " << testComp.getFrameRect().height
      << " width = " << testComp.getFrameRect().width << std::endl;
    testComp.removeShape(0);
    std::cout << "Now " << testComp.getLength() << " Figures here" << std::endl;
    std::shared_ptr<shalgueva::Shape> shape1 = testComp[0];
    shape1.reset();
    std::cout << "From Composite Shape2: " << std::endl;
    std::cout << "Now " << testComp.getLength() << " Figures here" << std::endl;
    shalgueva::CompositeShape testComp2(testComp);
    testComp2.addShape(rect1);
    shalgueva::CompositeShape test1(rect1);
    shalgueva::CompositeShape test2(testComp2);
    std::cout << "test1: " << test1.getLength() << " Figures here" << std::endl;
    std::cout << "test2: " << test2.getLength() << " Figures here" << std::endl;
    std::cout << "test1 getArea: " << test1.getArea() << std::endl;
    std::cout << "test1 getFrameRect: height = " << test1.getFrameRect().height
      << " width = " << test1.getFrameRect().width << std::endl;
  }

  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  
  catch (std::out_of_range & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }

  return 0;
}

