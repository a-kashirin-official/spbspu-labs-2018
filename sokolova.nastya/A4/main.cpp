#include <iostream>
#include <memory>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

//void printInfo(const sokolova::Shape & sh);
//void printInfoMatrix(const sokolova::Matrix & matr);

int main()
{
  try{
    sokolova::point_t centre{3.0, 7.0};
    sokolova::Circle circle(centre, 33.1);
    sokolova::point_t centre_rec{2.2, 0.0};
    sokolova::Rectangle rectangle(centre_rec, 3.7, 12.0);

    std::cout << "Circle:" << std::endl;
    circle.printInfo();
    circle.move( 1.3, 6.1 );
    circle.printInfo();
    circle.move( { 32.3, 47.1 } );
    circle.printInfo();
    circle.rotate(90);
    circle.printInfo();
    circle.scale(0.5);
    circle.printInfo();
    std::cout << std::endl;

    std::cout << "Rectangle:" << std::endl;
    rectangle.printInfo();
    rectangle.move( 5.30, -33.44 );
    rectangle.printInfo();
    rectangle.move( { 2.6, 18.17 } );
    rectangle.printInfo();
    rectangle.rotate(45);
    rectangle.printInfo();
    rectangle.scale(3.3);
    rectangle.printInfo();
    std::cout << std::endl;


    sokolova::point_t centre1{-6.8, 33.2};
    sokolova::Circle circle1(centre1, 8.0);
    sokolova::point_t centre_rec1{5.0, 0.0};
    sokolova::Rectangle rectangle1(centre_rec1, 22.8, 44.5);
    std::shared_ptr< sokolova::Shape > circlePtr1 = std::make_shared< sokolova::Circle >(circle1);
    std::shared_ptr< sokolova::Shape > rectanglePtr1 = std::make_shared< sokolova::Rectangle >(rectangle1);
    sokolova::CompositeShape compositeShape(circlePtr1);

    //std::cout << "Composite shape:" << std::endl;
    //printInfo(compositeShape);
    compositeShape.printInfo();
    compositeShape.addShape(rectanglePtr1);
    compositeShape.printInfo();
    compositeShape.rotate(90);
    compositeShape.printInfo();
    compositeShape.scale(2.0);
    compositeShape.printInfo();
    compositeShape.removeShape(1);
    compositeShape.printInfo();
    compositeShape.deleteAllShapes();
    compositeShape.printInfo();
    std::cout << std::endl;

    sokolova::point_t centre_circ{4.8, 1.0};
    sokolova::Circle circleM(centre_circ, 2.5);
    sokolova::point_t centre_rect1{88.0, 100.0};
    sokolova::Rectangle rectangleM1(centre_rect1, 2.0, 2.0);
    sokolova::point_t centre_rect2{1.0, 7.0};
    sokolova::Rectangle rectangleM2(centre_rect2, 6.7, 2.1);

    std::shared_ptr<sokolova::Shape> rectanglePtr = std::make_shared<sokolova::Rectangle>(rectangleM1);
    std::shared_ptr<sokolova::Shape> circlePtr = std::make_shared<sokolova::Circle>(circleM);
    std::shared_ptr<sokolova::Shape> rectPtr = std::make_shared<sokolova::Rectangle>(rectangleM2);

    sokolova::CompositeShape compSh(rectanglePtr);
    compSh.addShape(circlePtr);
    compSh.addShape(rectPtr);

    sokolova::Matrix matrix;
    matrix.add(circlePtr);
    matrix.add(rectanglePtr);
    matrix.add(rectPtr);
    matrix.addElementsFromCompSh(compSh);
    matrix.printInfo();

  }
  catch (std::exception & error) {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  catch (...) {
    std::cerr << "Something was wrong" << std::endl;
    return 2;
  }
  return 0;
}

