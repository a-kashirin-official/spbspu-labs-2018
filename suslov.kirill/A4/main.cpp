#include <iostream>
#include <memory>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

void showInfo(const suslov::Shape & shape)
{
  std::cout << "Width of the frame:\t";
  std::cout << shape.getFrameRect().width << std::endl;
  std::cout << "Height of the frame:\t";
  std::cout << shape.getFrameRect().height << std::endl;
  std::cout << "Center of the frame\t(" << shape.getFrameRect().pos.x << ", "
  << shape.getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Sum of the areas:\t";
  std::cout << shape.getArea() << std::endl;
  std::cout << "Angle:\t"; 
  std::cout << shape.getAngle() << std::endl << std::endl;
 }

int main()
{
  try{
    suslov::Circle circle({20.0, 2.0}, 30.0);
    suslov::Rectangle rectangle({60.0, 4.0}, 40.0, 20.0);
   
    std::cout << "First shape (Circle): " << std::endl;
    showInfo(circle);

    std::cout << "Second shape (Rectangle): " << std::endl;
    showInfo(rectangle);

    std::cout << "=======================================" << std::endl << std::endl;

    std::cout << "Rotate first shape 90 degrees" << std::endl;
    circle.rotate(90.0);
    showInfo(circle);

    std::cout << "Rotate second shape 45 degrees" << std::endl;
    rectangle.rotate(45.0);
    showInfo(rectangle);

    std::cout << "Rotate second shape 45 degrees" << std::endl;
    rectangle.rotate(45.0);
    showInfo(rectangle);

    std::cout << "Rotate second shape 45 degrees" << std::endl;
    rectangle.rotate(45.0);
    showInfo(rectangle);

    std::cout << "Rotate second shape 45 degrees" << std::endl;
    rectangle.rotate(45.0);
    showInfo(rectangle);

    std::cout << "Composite shape:" << std::endl << std::endl;

    suslov::Rectangle compositeRectangle({200.0, 150.0}, 80.0, 70.0);
    suslov::Rectangle compositeRectangle2({100.0, 70.0}, 30.0, 90.0);
    std::shared_ptr < suslov::Shape > pCompRectangle = std::make_shared < suslov::Rectangle > (compositeRectangle);
    std::shared_ptr < suslov::Shape > pCompRectangle2 = std::make_shared < suslov::Rectangle > (compositeRectangle2);
    suslov::CompositeShape compositeShape(pCompRectangle);

    std::cout << "First shape (Rectangle): " << std::endl;
    showInfo(compositeRectangle);

    std::cout << "Second shape (Rectangle): " << std::endl;
    showInfo(compositeRectangle2);

    std::cout << "=======================================" << std::endl << std::endl;
    std::cout << "Composite shape with first shape:" << std::endl << std::endl;
    showInfo(compositeShape);

    std::cout << "Second shape was added:" << std::endl << std::endl;
    compositeShape.addShape(pCompRectangle2);
    showInfo(compositeShape);

    std::cout << "Rotate 45 degrees" << std::endl << std::endl;
    compositeShape.rotate(45.0);
    showInfo(compositeShape);

    std::cout << "Rotate 45 degrees" << std::endl << std::endl;
    compositeShape.rotate(45.0);
    showInfo(compositeShape);

    suslov::Circle matrixCircle{ { 0.0, 0.0 }, 2.0 };
    suslov::Rectangle matrixRectangle{ { 1.0, 0.0 }, 2.0, 2.0 };
    suslov::Rectangle matrixRectangle2{ { -3.0, 0.0 }, 4.0, 4.0 };
    suslov::Circle matrixCircle2{ { 3.0, 2.0 }, 5.0 };

    std::shared_ptr< suslov::Shape > pMatrixCircle = std::make_shared< suslov::Circle >(matrixCircle);
    std::shared_ptr< suslov::Shape > pMatrixRectangle = std::make_shared< suslov::Rectangle >(matrixRectangle);
    std::shared_ptr< suslov::Shape > pMatrixRectangle2 = std::make_shared< suslov::Rectangle >(matrixRectangle2);
    std::shared_ptr< suslov::Shape > pMatrixCircle2 = std::make_shared< suslov::Circle >(matrixCircle2);

    suslov::Matrix matrix(pMatrixCircle);
    matrix.addShape(pMatrixRectangle);
    matrix.addShape(pMatrixRectangle2);
    matrix.addShape(pMatrixCircle2);

    std::cout << "Matrix:" << std::endl << std::endl;
    std::unique_ptr< std::shared_ptr< suslov::Shape >[] > layer1 = matrix[0];
    std::unique_ptr< std::shared_ptr< suslov::Shape >[] > layer2 = matrix[1];
    std::unique_ptr< std::shared_ptr< suslov::Shape >[] > layer3 = matrix[2];

    std::cout << "Circle:" << std::endl;
    showInfo(*layer1[0]);
    std::cout << "Rectangle:" << std::endl;
    showInfo(*layer2[0]);
    std::cout << "Rectangle2:" << std::endl;
    showInfo(*layer2[1]);
    std::cout << "Circle2:" << std::endl;
    showInfo(*layer3[0]);
  } catch(std::invalid_argument & e) {
    std::cerr << e.what() << std::endl;
  } catch(std::out_of_range & e) {
    std::cerr << e.what() << std::endl;
  } catch(...) {
    std::cerr << "Exception" << std::endl;
  }

  return 0;
}
