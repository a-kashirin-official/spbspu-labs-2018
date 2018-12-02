#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include <iostream>
#include <memory>

using namespace kashirin;

void getInf(const Shape & figure)
{
  std::cout << "Area= " << figure.getArea() << std::endl;
  std::cout << "FrameRect: " << std::endl;
  std::cout << "width, height" << figure.getFrameRect().width << "  " << figure.getFrameRect().height << std::endl;
  std::cout << "center" << figure.getFrameRect().pos.x << " , " << figure.getFrameRect().pos.y << std::endl;
  std::cout << " " << std::endl;
}

int main()
{

  try{
    Rectangle rect{ 4.0, 4.0, { 2.5, 2.5} };
    Circle circ{ 1.0, { 6.0, 6.0 } };
    Triangle trian{ { 3.0, 3.0 }, { 5.0, 3.0 }, { 3.0, 5.0 } };
    std::shared_ptr< Shape > rectPtr = std::make_shared< Rectangle >(rect);
    std::shared_ptr< Shape > circPtr = std::make_shared< Circle >(circ);
    std::shared_ptr< Shape > trianPtr = std::make_shared< Triangle >(trian);

    CompositeShape comp1(rectPtr);
    std::cout << "CompositeShape1" << std::endl;
    comp1.addShape(circPtr);
    getInf(comp1);
    std::cout << "rotate 45" << std::endl;
    comp1.rotate(45);
    getInf(comp1);

    std::cout << "Rect" << std::endl;
    getInf(rect);
    std::cout << "rotate 45" << std::endl;
    rect.rotate(55);
    getInf(rect);

    std::cout << "Circ" << std::endl;
    getInf(circ);
    std::cout << "rotate 45" << std::endl;
    circ.rotate(45);
    getInf(circ);

    std::cout << "Trian" << std::endl;
    getInf(trian);
    std::cout << "rotate 45" << std::endl;
    trian.rotate(45);
    getInf(trian);

    Rectangle rect1{ 4.0, 4.0, { 2.5, 2.5} };
    Circle circ1{ 1.0, { 6.0, 6.0 } };
    Triangle trian1{ { 3.0, 3.0 }, { 5.0, 3.0 }, { 3.0, 5.0 } };
    Rectangle rect2{ 4.0, 4.0, { 6.0, 2.0 } };

    std::shared_ptr< Shape > rect1Ptr = std::make_shared< Rectangle >(rect1);
    std::shared_ptr< Shape > rect2Ptr = std::make_shared< Rectangle >(rect2);
    std::shared_ptr< Shape > circ1Ptr = std::make_shared< Circle >(circ1);
    std::shared_ptr< Shape > trian1Ptr = std::make_shared< Triangle >(trian1);

    std::cout << "Matrix" << std::endl;
    Matrix matrix(rect1Ptr);
    matrix.addShape(circ1Ptr);
    matrix.addShape(trian1Ptr);
    matrix.addShape(rect2Ptr);

    std::unique_ptr<std::shared_ptr< Shape >[] > layer1 = matrix[0];
    std::unique_ptr<std::shared_ptr< Shape >[] > layer2 = matrix[1];
    std::unique_ptr<std::shared_ptr< Shape >[] > layer3 = matrix[2];

    std::cout << "rectangle" << std::endl;
    getInf(*layer1[0]);
    std::cout << "circle" << std::endl;
    getInf(*layer1[1]);
    std::cout << "triangle" << std::endl;
    getInf(*layer2[0]);
    std::cout << "rect1" << std::endl;
    getInf(*layer3[0]);

  }
  catch(const std::invalid_argument & e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  catch(const std::out_of_range & e) {
    std::cerr << e.what() << std::endl;
  }
  catch(...) {
    std::cerr << "exception" << std::endl;
  }

  return 0;
}  
    
