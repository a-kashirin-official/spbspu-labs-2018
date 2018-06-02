#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include <iostream>
#include <memory>

void showInfo(const kahuanahil::Shape &shape)
{
  std::cout << "Width: " << shape.getFrameRect().width << std::endl;
  std::cout << "Height: " << shape.getFrameRect().height << std::endl;
  std::cout << "Center( " << shape.getFrameRect().pos.x << "; " << shape.getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Area: " << shape.getArea() << std::endl;
  std::cout << "Angle: " << shape.getAngle() << std::endl;
}

int main()
{
  try{
    kahuanahil::Circle cir(10.0, {5.0, 2.0});
    kahuanahil::Rectangle rec(10.0, 15.0, {10.0, 4.0});
   
    std::cout << "First shape (Circle): " << std::endl;
    showInfo(cir);

    std::cout << "Second shape (Rectangle): " << std::endl;
    showInfo(rec);

    std::cout << "Rotate Circle 60 degrees" << std::endl;
    cir.rotate(60.0);
    showInfo(cir);

    std::cout << "Rotate Rectangle 90 degrees" << std::endl;
    rec.rotate(90.0);
    showInfo(rec);

    std::cout << "Rotate Rectangle 45 degrees" << std::endl;
    rec.rotate(45.0);
    showInfo(rec);

    std::cout << "Rotate second shape 130 degrees" << std::endl;
    rec.rotate(130.0);
    showInfo(rec);

    std::cout << "Composite shape:" << std::endl << std::endl;

    kahuanahil::Rectangle compositeRec(80.0, 70.0, {200.0, 150.0});
    kahuanahil::Rectangle compositeRec2(30.0, 90.0, {100.0, 70.0});
    std::shared_ptr < kahuanahil::Shape > pCompRectangle = std::make_shared < kahuanahil::Rectangle > (compositeRec);
    std::shared_ptr < kahuanahil::Shape > pCompRectangle2 = std::make_shared < kahuanahil::Rectangle > (compositeRec2);
    kahuanahil::CompositeShape compositeShape(pCompRectangle);

    std::cout << "First shape (Rectangle): " << std::endl;
    showInfo(compositeRec);

    std::cout << "Second shape (Rectangle): " << std::endl;
    showInfo(compositeRec2);

    std::cout << "Composite shape with first Rectangle:" << std::endl << std::endl;
    showInfo(compositeShape);

    std::cout << "Second shape added:" << std::endl << std::endl;
    compositeShape.addShape(pCompRectangle2);
    showInfo(compositeShape);

    std::cout << "Rotate 60 degrees" << std::endl << std::endl;
    compositeShape.rotate(60.0);
    showInfo(compositeShape);

    std::cout << "Rotate 90 degrees" << std::endl << std::endl;
    compositeShape.rotate(90.0);
    showInfo(compositeShape);

    kahuanahil::Circle mCircle{2.0, { 0.0, 0.0 }};
    kahuanahil::Circle mCircle2{5.0, { 3.0, 2.0 }};
    kahuanahil::Rectangle mRectangle{2.0, 2.0, { 1.0, 0.0 }};
    kahuanahil::Rectangle mRectangle2{4.0, 4.0, { -3.0, 0.0 }};
    
    std::shared_ptr< kahuanahil::Shape > pMatrixCircle = std::make_shared< kahuanahil::Circle >(mCircle);
    std::shared_ptr< kahuanahil::Shape > pMatrixCircle2 = std::make_shared< kahuanahil::Circle >(mCircle2);
    std::shared_ptr< kahuanahil::Shape > pMatrixRectangle = std::make_shared< kahuanahil::Rectangle >(mRectangle);
    std::shared_ptr< kahuanahil::Shape > pMatrixRectangle2 = std::make_shared< kahuanahil::Rectangle >(mRectangle2);
    
    kahuanahil::Matrix matrix(pMatrixCircle);
    matrix.addShape(pMatrixCircle2);
    matrix.addShape(pMatrixRectangle);
    matrix.addShape(pMatrixRectangle2);
   
    std::cout << "Matrix:" << std::endl << std::endl;
    std::unique_ptr< std::shared_ptr< kahuanahil::Shape >[] > layer1 = matrix[0];
    std::unique_ptr< std::shared_ptr< kahuanahil::Shape >[] > layer2 = matrix[1];
    std::unique_ptr< std::shared_ptr< kahuanahil::Shape >[] > layer3 = matrix[2];

    std::cout << "Circle:" << std::endl;
    showInfo(*layer1[0]);
    std::cout << "Circle2:" << std::endl;
    showInfo(*layer3[0]);
    std::cout << "Rectangle:" << std::endl;
    showInfo(*layer2[0]);
    std::cout << "Rectangle2:" << std::endl;
    showInfo(*layer2[1]);

  } catch(std::invalid_argument &a) {
    std::cerr << a.what() << std::endl;
  } catch(std::out_of_range &e) {
    std::cerr << e.what() << std::endl;
  } catch(...) {
    std::cerr << "Exception" << std::endl;
  }
  return 0;
}
