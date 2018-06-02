#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include <iostream>
#include <memory>

using namespace dumaev;

void printInfo(const Shape &shape)
{
  std::cout << "\tArea: " << shape.getArea() << "\n"
            << "\tHeight of frame rectangle:" << shape.getFrameRect().height << "\n"
            << "\tWidth of frame rectangle:" << shape.getFrameRect().width << "\n"
            << "\tCoordinates of frame rectangle: (" << shape.getFrameRect().pos.x
            << "," << shape.getFrameRect().pos.y << ")" << std::endl;
}
int main()
{
  try
  {
    Circle circle({1, 1}, 9);
    std::cout << "CIRCLE" << std::endl;
    printInfo(circle);
    std::cout << "Move to point (12, 3)" << std::endl;
    circle.move({12, 3});
    printInfo(circle);
    std::cout << "Move on dx = -5, dy = 2" << std::endl;
    circle.move(-5, 2);
    printInfo(circle);
    std::cout << "Scaling with coefficient = 3" << std::endl;
    circle.scale(3);
    printInfo(circle);
    circle.rotate(60);
    std::cout << "60 degree turn" << std::endl;
    printInfo(circle);

    Rectangle rectangle({0, 0}, 20, 15);
    std::cout << "RECTANGLE" << std::endl;
    printInfo(rectangle);
    std::cout << "Move to point (5, 5)" << std::endl;
    rectangle.move({5, 5});
    printInfo(rectangle);
    std::cout << "Move on dx = 1, dy = 1" << std::endl;
    rectangle.move(1, 1);
    printInfo(rectangle);
    std::cout << "Scaling with coefficient = 2" << std::endl;
    rectangle.scale(2);
    printInfo(rectangle);
    rectangle.rotate(60);
    std::cout << "60 degree turn" << std::endl;
    printInfo(rectangle);

    std::shared_ptr<Shape> circlePtr = std::make_shared<Circle>(circle);
    std::shared_ptr<Shape> rectanglePtr = std::make_shared<Rectangle>(rectangle);
    CompositeShape compositeShape(circlePtr);
    compositeShape.addShape(rectanglePtr);
    std::cout << "COMPOSITE SHAPE: rectangle and circle" << std::endl;
    printInfo(compositeShape);
    std::cout << "Move to point (9, 7)" << std::endl;
    compositeShape.move({9, 7});
    printInfo(compositeShape);
    std::cout << "Move on dx = 2, dy = 2" << std::endl;
    compositeShape.move(2, 2);
    printInfo(compositeShape);
    std::cout << "Scaling with coefficient = 2" << std::endl;
    compositeShape.scale(2);
    printInfo(compositeShape);
    compositeShape.rotate(90);
    std::cout << "90 degree turn" << std::endl;
    printInfo(compositeShape);

    Circle circleM1({-2,2}, 1);
    Rectangle rectangleM1({-1, 1}, 2, 2);
    Rectangle rectangleM2({-2, 0}, 2, 4);
    Rectangle rectangleM3({-4, -2}, 4, 2);
    Rectangle rectangleM4({-3, -3}, 4, 4);
    std::shared_ptr< Shape > circlePtrM1 = std::make_shared< Circle >(circleM1);
    std::shared_ptr< Shape > rectanglePtrM1 =std::make_shared< Rectangle >(rectangleM1);
    std::shared_ptr< Shape > rectanglePtrM2 =std::make_shared< Rectangle >(rectangleM2);
    std::shared_ptr< Shape > rectanglePtrM3 =std::make_shared< Rectangle >(rectangleM3);
    std::shared_ptr< Shape > rectanglePtrM4 =std::make_shared< Rectangle >(rectangleM4);

    Matrix matrix(circlePtrM1);
    matrix.addShape(rectanglePtrM1);
    matrix.addShape(rectanglePtrM2);
    matrix.addShape(rectanglePtrM3);
    matrix.addShape(rectanglePtrM4);

    std::cout << "MATRIX:" << std::endl;
    std::unique_ptr< std::shared_ptr< Shape >[] > layer1 = matrix[0];
    std::unique_ptr< std::shared_ptr< Shape >[] > layer2 = matrix[1];
    std::unique_ptr< std::shared_ptr< Shape >[] > layer3 = matrix[2];

    if (layer1[0] == circlePtrM1)
    {
      std::cout << "\t1 element in 1 layer is circle" << std::endl;
    }
    if (layer1[1] == rectanglePtrM3)
    {
      std::cout << "\t2 element in 1 layer is rectangle 3" << std::endl;
    }
    if (layer2[0] == rectanglePtrM1)
    {
      std::cout << "\t1 element in 2 layer is rectangle 1" << std::endl;
    }
    if (layer2[1] == rectanglePtrM4)
    {
      std::cout << "\t2 element in 2 layer is rectangle 4" << std::endl;
    }
    if (layer3[0] == rectanglePtrM2)
    {
      std::cout << "\t1 element in 3 layer is rectangle 2" << std::endl;
    }
    if (layer3[1] == nullptr)
    {
      std::cout << "\t2 element in 3 layer is nullptr" << std::endl;
    }
  } catch (std::invalid_argument & e){
    std::cerr << e.what() << std::endl;
  } catch (std::out_of_range & e) {
    std::cerr << e.what() << std::endl;
  } catch (...) {
    std::cerr << "Exception occured" << std::endl;
  }

  return 0;
}
