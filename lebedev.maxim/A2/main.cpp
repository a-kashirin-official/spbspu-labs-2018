#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

using namespace lebedev;

void printShapeInfo (Shape & shape)
{
  shape.printCurrentInfo();
  std::cout << "Area:" << shape.getArea() << std::endl;
  std::cout << "FrameRect center (x,y): " << shape.getFrameRect().pos.x << ", " << shape.getFrameRect().pos.y << std::endl;
  std::cout << "FrameRect width:" << shape.getFrameRect().width << std::endl;
  std::cout << "FrameRect height:" << shape.getFrameRect().height << std::endl;
}

int main()
{
  try
  {
    std::cout << "SIRCLE\n" << std::endl;

    Circle testCircle({3.0,4.25},7.5);
    printShapeInfo(testCircle);
    std::cout << "\n" << std::endl;
    testCircle.move({-2.5,10.3});
    printShapeInfo(testCircle);
    std::cout << "\n" << std::endl;
    testCircle.move(8.7,3.0);
    printShapeInfo(testCircle);
    std::cout << "\n" << std::endl;
    testCircle.scale(0.5);
    printShapeInfo(testCircle);
    std::cout << "\n" << std::endl;

    std::cout << "RECTANGLE\n" << std::endl;

    Rectangle testRect({1.0,0.75},2.0,8.0);
    printShapeInfo(testRect);
    std::cout << "\n" << std::endl;
    testRect.move({-2.0,4.5});
    printShapeInfo(testRect);
    std::cout << "\n" << std::endl;
    testRect.move(8.5,0.7);
    printShapeInfo(testRect);
    std::cout << "\n" << std::endl;
    testRect.scale(3.0);
    printShapeInfo(testRect);
    std::cout << "\n" << std::endl;

    std::cout << "TRIANGLE\n" << std::endl;

    Triangle testTria({1.0,3.0},{4.0,1.0},{6.0,4.0});
    printShapeInfo(testTria);
    std::cout << "\n" << std::endl;
    testTria.move({2.5,4.6});
    printShapeInfo(testTria);
    std::cout << "\n" << std::endl;
    testTria.move(8.7,3.0);
    printShapeInfo(testTria);
    std::cout << "\n" << std::endl;
  }
  catch(std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }

  return 0;
}
