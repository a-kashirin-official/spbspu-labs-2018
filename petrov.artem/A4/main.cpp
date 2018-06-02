#include <iostream>
#include <memory>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

void printInfo(const petrov::Shape & object)
{
  std::cout << "Area: " << object.getArea() << std::endl;
  const petrov::rectangle_t frame = object.getFrameRect();
  std::cout << "Frame for object:" << std::endl;
  std::cout << "\tMiddle of frame: " << frame.pos.x << ", " << frame.pos.y << std::endl;
  std::cout << "\tWidth of frame: " << frame.width << std::endl;
  std::cout << "\tHeight of frame: " << frame.height << std::endl;
}

int main()
{
  try{
    petrov::Circle circle{ { 5.32, 27.63 }, 10.01 };
    petrov::Rectangle rectangle{ { 25.04, 6.12 }, 7.13, 4.82 };
    std::shared_ptr< petrov::Shape > circlePtr = std::make_shared< petrov::Circle >(circle);
    std::shared_ptr< petrov::Shape > rectanglePtr = std::make_shared< petrov::Rectangle >(rectangle);

    std::cout << "Circle:" << std::endl;
    printInfo(circle);
    circle.move( 2.45, 6.16 );
    printInfo(circle);
    circle.move( { 52.90, 73.21 } );
    printInfo(circle);
    circle.rotate(90);
    printInfo(circle);
    circle.scale(3.0);
    printInfo(circle);
    std::cout << std::endl;

    std::cout << "Rectangle:" << std::endl;
    printInfo(rectangle);
    rectangle.move( -5.23, 19.08 );
    printInfo(rectangle);
    rectangle.move( { 3.03, 21.17 } );
    printInfo(rectangle);
    rectangle.rotate(90);
    printInfo(rectangle);
    rectangle.scale(1.5);
    printInfo(rectangle);
    std::cout << std::endl;


    petrov::Circle circle1{ { -2.0, -2.0 }, 1.0 };
    petrov::Rectangle rectangle1{ { 2.0, 2.0 }, 2.0, 2.0 };
    std::shared_ptr< petrov::Shape > circlePtr1 = std::make_shared< petrov::Circle >(circle1);
    std::shared_ptr< petrov::Shape > rectanglePtr1 = std::make_shared< petrov::Rectangle >(rectangle1);
    petrov::CompositeShape compositeShape(circlePtr1);

    std::cout << "Composite shape:" << std::endl;
    printInfo(compositeShape);
    compositeShape.addShape(rectanglePtr1);
    printInfo(compositeShape);
    compositeShape.rotate(90);
    printInfo(compositeShape);
    compositeShape.scale(2.0);
    printInfo(compositeShape);
    compositeShape.removeShape(1);
    printInfo(compositeShape);
    compositeShape.deleteShapes();
    printInfo(compositeShape);
    std::cout << std::endl;

    petrov::Circle circleM{ { -2.0, -2.0 }, 2.0 };
    petrov::Rectangle rectangleM1{ { -2.0, 0.0 }, 2.0, 2.0 };
    petrov::Rectangle rectangleM2{ { 1.0, 1.0 }, 6.0, 3.0 };
    petrov::Rectangle rectangleM3{ { 3.0, 1.0 }, 2.0, 4.0 };
    petrov::Rectangle rectangleM4{ { 3.0, 3.0 }, 4.0, 4.0 };

    std::shared_ptr< petrov::Shape > circlePtrM = std::make_shared< petrov::Circle >(circleM);
    std::shared_ptr< petrov::Shape > rectanglePtrM1 = std::make_shared< petrov::Rectangle >(rectangleM1);
    std::shared_ptr< petrov::Shape > rectanglePtrM2 = std::make_shared< petrov::Rectangle >(rectangleM2);
    std::shared_ptr< petrov::Shape > rectanglePtrM3 = std::make_shared< petrov::Rectangle >(rectangleM3);
    std::shared_ptr< petrov::Shape > rectanglePtrM4 = std::make_shared< petrov::Rectangle >(rectangleM4);

    petrov::Matrix matrix(circlePtrM);
    matrix.addShape(rectanglePtrM1);
    matrix.addShape(rectanglePtrM2);
    matrix.addShape(rectanglePtrM3);
    matrix.addShape(rectanglePtrM4);

    std::cout << "Matrix:" << std::endl;
    std::unique_ptr< std::shared_ptr< petrov::Shape >[] > layer1 = matrix[0];
    std::unique_ptr< std::shared_ptr< petrov::Shape >[] > layer2 = matrix[1];
    std::unique_ptr< std::shared_ptr< petrov::Shape >[] > layer3 = matrix[2];



    if (layer1[0] == circlePtrM)
    {
      std::cout << "\t1 element in first layer is circle" << std::endl;
    }
    if (layer1[1] == rectanglePtrM3)
    {
      std::cout << "\t2 element in first layer is rectangle 3" << std::endl;
    }
    if (layer2[0] == rectanglePtrM1)
    {
      std::cout << "\t1 element in second layer is rectangle 1" << std::endl;
    }
    if (layer2[1] == rectanglePtrM4)
    {
      std::cout << "\t2 element in second layer is rectangle 4" << std::endl;
    }
    if (layer3[0] == rectanglePtrM2)
    {
      std::cout << "\t1 element in third layer is rectangle 2" << std::endl;
    }
    if (layer3[1] == nullptr)
    {
      std::cout << "\t2 element in third layer is nullptr" << std::endl;
    }
  } catch(std::invalid_argument & e) {
    std::cerr << e.what() << std::endl;
  } catch(std::out_of_range & e) {
    std::cerr << e.what() << std::endl;
  } catch(...) {
    std::cerr << "Exception occured" << std::endl;
  }

  return 0;
}
