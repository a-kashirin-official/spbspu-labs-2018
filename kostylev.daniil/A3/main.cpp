#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "cmath"

void printShapeInfo(const kostylev::Shape & figure)
{
  const kostylev::rectangle_t frame = figure.getFrameRect();
  std::cout << "Area = " << figure.getArea() << std::endl;
  std::cout << "Parameters of frame rectangle for this figure:" << std::endl;
  std::cout << "  Center: " << "(" << frame.pos.x << ", " << frame.pos.y << ")" << std::endl;
  std::cout << "  Width = " << frame.width << std::endl;
  std::cout << "  Height = " << frame.height << std::endl;
}

int main()
{
  try
  {
    kostylev::Rectangle rectangle{{37.04, 29.45}, 9.67, 5.31};

    std::cout << "Rectangle:" << std::endl;
    printShapeInfo(rectangle);
    rectangle.move({26.05, 19.81});
    printShapeInfo(rectangle);
    rectangle.move(7.19, 1.36);
    printShapeInfo(rectangle);
    rectangle.scale(3.0);
    printShapeInfo(rectangle);

    kostylev::Circle circle{{7.91, 19.42}, 8.34};

    std::cout << "Circle:" << std::endl;
    printShapeInfo(circle);
    circle.move({25.31, 48.07});
    printShapeInfo(circle);
    circle.move(1.15, 2.12);
    printShapeInfo(circle);
    circle.scale(2.5);
    printShapeInfo(circle);

    std::cout << "[CompositeShape]" << std::endl;
    std::shared_ptr<kostylev::Shape> testRect =
      std::make_shared<kostylev::Rectangle>(kostylev::Rectangle({25.0, 25.0}, 10.0, 10.0));
    std::shared_ptr<kostylev::Shape> testCirc =
      std::make_shared<kostylev::Circle>(kostylev::Circle({50.0, 50.0}, 10));
    kostylev::CompositeShape testComp(testRect);
    testComp.addShape(testCirc);
    std::cout << "From Composite Shape1: " << std::endl;
    std::cout << testComp.getLength() << " Figures here" << std::endl;
    std::cout << "testComp getArea: " << testComp.getArea() << std::endl;
    std::cout << "testComp getFrameRect: height = " << testComp.getFrameRect().height
      << " width = " << testComp.getFrameRect().width << std::endl;
    testComp.removeShape(0);
    std::cout << "Now " << testComp.getLength() << " Figures here" << std::endl;
    std::shared_ptr<kostylev::Shape> shape = testComp[0];
    shape.reset();
    std::cout << "From Composite Shape2: " << std::endl;
    std::cout << "Now " << testComp.getLength() << " Figures here" << std::endl;
    kostylev::CompositeShape testComp2(testComp);
    testComp2.addShape(testRect);
    kostylev::CompositeShape test1(testRect);
    kostylev::CompositeShape test2(testComp2);
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
  return 0;
}
