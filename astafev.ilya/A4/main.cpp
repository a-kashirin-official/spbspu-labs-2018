

#include <iostream>
#include <memory>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

using namespace astafev;
int main()
{

  Circle circle{ { 5.32, 27.63 }, 10.01 };
  Rectangle rectangle{ { 25.04, 6.12 }, 7.13, 4.82 };
  std::shared_ptr< Shape > circlePtr = std::make_shared<Circle >(circle);
  std::shared_ptr< Shape > rectanglePtr = std::make_shared<Rectangle >(rectangle);


  Circle circle1{ { -2.0, -2.0 }, 1.0 };
  Rectangle rectangle1{ { 2.0, 2.0 }, 2.0, 2.0 };
  std::shared_ptr< Shape > circlePtr1 = std::make_shared< Circle >(circle1);
  std::shared_ptr< Shape > rectanglePtr1 = std::make_shared< Rectangle >(rectangle1);
  CompositeShape compositeShape(circlePtr1);
  rectangle1.printInfo();
  circle1.printInfo();

  compositeShape.addElement(rectanglePtr1);
  compositeShape.rotate(45);
  compositeShape.scale(2.0);
  compositeShape.addElement(rectanglePtr);

  Circle circleM{ { -2.0, -2.0 }, 2.0 };
  Rectangle rectangleM1{ { -2.0, 0.0 }, 2.0, 2.0 };
  Rectangle rectangleM2{ { 1.0, 1.0 }, 6.0, 3.0 };
  Rectangle rectangleM3{ { 3.0, 1.0 }, 2.0, 4.0 };
  Rectangle rectangleM4{ { 3.0, 3.0 }, 4.0, 4.0 };
  compositeShape.printInfo();
  std::shared_ptr< Shape > comp = std::make_shared< CompositeShape >(compositeShape);
  std::shared_ptr< Shape > circlePtrM = std::make_shared< Circle >(circleM);
  std::shared_ptr< Shape > rectanglePtrM1 = std::make_shared< Rectangle >(rectangleM1);
  std::shared_ptr< Shape > rectanglePtrM2 = std::make_shared< Rectangle >(rectangleM2);
  std::shared_ptr< Shape > rectanglePtrM3 = std::make_shared< Rectangle >(rectangleM3);
  std::shared_ptr< Shape > rectanglePtrM4 = std::make_shared< Rectangle >(rectangleM4);

  Matrix matrix(circlePtrM);
  matrix.addElement(comp);
  matrix.addElement(rectanglePtrM1);
  matrix.addElement(rectanglePtrM2);
  matrix.addElement(rectanglePtrM3);
  matrix.addElement(rectanglePtrM4);

  std::cout << "Matrix:" << std::endl;
  matrix.printInfo();

  return 0;
}


