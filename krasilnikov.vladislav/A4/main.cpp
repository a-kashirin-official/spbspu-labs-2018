#include <iostream>
#include <memory>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

using namespace krasilnikov;

void printInfo(const Shape & object)
{
  std::cout <<"Area: " << object.getArea() << std::endl;
  const rectangle_t frame = object.getFrameRect();
  std::cout << "Object frame:" << std::endl;
  std::cout << "Frame tMiddle: " << frame.pos.x << ", " << frame.pos.y <<std::endl;
  std::cout << "Frame tWidth: " << frame.width << std::endl;
  std::cout << "Frame tHeight: " << frame.height << std::endl;
}

int main()
{
  try{
    Rectangle rect(11.9, 13.1, {13.0, 7.0});
    Circle circ({13.0, 7.0}, 16.9);
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle > (rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle > (circ);

    std::cout << "Rectangle:" << std::endl;
    printInfo(rect);
    rect.move({-1.8, 1.7});
    printInfo(rect);
    rect.move(-1.8, 1.7);
    printInfo(rect);
    rect.scale(5);
    printInfo(rect);
    rect.rotate(45);
    printInfo(rect);
    std::cout << std::endl;

    std::cout << "Circle:" << std::endl;
    printInfo(circ);
    circ.move({-1.8, 1.7});
    printInfo(circ);
    circ.move(-1.8, 1.7);
    printInfo(circ);
    circ.scale(5);
    printInfo(circ);
    circ.rotate(45);
    printInfo(circ);
    std::cout << std::endl;

    Rectangle rect1(13.1, 11.9, {7.0, 13.0});
    Circle circ1({7.0, 13.0}, 13.5);
    std::shared_ptr< Shape > rectPtr1 = std::make_shared< Rectangle > (rect1);
    std::shared_ptr< Shape > circPtr1 = std::make_shared< Circle > (circ1);
    CompositeShape cs(rectPtr1);

    std::cout << "Composite shape:" << std::endl;
    printInfo(cs);
    cs.addShape(circPtr1);
    printInfo(cs);
    cs.scale(5.0);
    printInfo(cs);
    cs.rotate(45);
    printInfo(cs);
    cs.removeShape(1);
    printInfo(cs);
    cs.clear();
    printInfo(cs);
    std::cout << std::endl;

    Circle circM( { -2.0, -2.0 }, 2.0 );
    Rectangle rectM1( 2.0, 2.0, { -2.0, 0.0 } );
    Rectangle rectM2( 6.0, 3.0, { 1.0, 1.0 } );
    Rectangle rectM3( 2.0, 4.0, { 3.0, 1.0 } );
    Rectangle rectM4( 4.0, 4.0, { 3.0, 3.0 } );

    std::shared_ptr< Shape > circMPtr = std::make_shared< Circle >(circM);
    std::shared_ptr< Shape > rectM1Ptr = std::make_shared< Rectangle >(rectM1);
    std::shared_ptr< Shape > rectM2Ptr = std::make_shared< Rectangle >(rectM2);
    std::shared_ptr< Shape > rectM3Ptr = std::make_shared< Rectangle >(rectM3);
    std::shared_ptr< Shape > rectM4Ptr = std::make_shared< Rectangle >(rectM4);

    Matrix matrix(circMPtr);
    matrix.addShape(rectM1Ptr);
    matrix.addShape(rectM2Ptr);
    matrix.addShape(rectM3Ptr);
    matrix.addShape(rectM4Ptr);

    std::cout << "Matrix:" << std::endl;
    std::unique_ptr< std::shared_ptr< Shape >[] > layer1 = matrix[0];
    std::unique_ptr< std::shared_ptr< Shape >[] > layer2 = matrix[1];
    std::unique_ptr< std::shared_ptr< Shape >[] > layer3 = matrix[2];



    if (layer1[0] == circMPtr)
    {
      std::cout << "\t1 element in first layer is circ" << std::endl;
    }
    if (layer1[1] == rectM3Ptr)
    {
      std::cout << "\t2 element in first layer is rect 3" << std::endl;
    }
    if (layer2[0] == rectM1Ptr)
    {
      std::cout << "\t1 element in second layer is rect 1" << std::endl;
    }
    if (layer2[1] == rectM2Ptr)
    {
      std::cout << "\t2 element in second layer is rect 2" << std::endl;
    }
    if (layer3[0] == rectM4Ptr)
    {
      std::cout << "\t1 element in third layer is rect 4" << std::endl;
    }
    if (layer3[1] == nullptr)
    {
      std::cout << "\t2 element in third layer is nullptr" << std::endl;
    }
  } catch(std::invalid_argument & error) {
    std::cerr << error.what() << std::endl;
  } catch(std::out_of_range & error) {
    std::cerr << error.what() << std::endl;
  } catch(...) {
    std::cerr << "Exception occured" << std::endl;
  }

  return 0;
}
