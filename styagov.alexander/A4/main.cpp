#include <iostream>
#include <memory>

#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

using namespace styagov;

void printShapeCoordinates(const styagov::Shape & shape)
{
  std::cout << "Center (";
  std::cout << shape.getPos().x << "; ";
  std::cout << shape.getPos().y << "), ";
  std::cout << "frame rectangle center (";
  std::cout << shape.getFrameRect().pos.x << "; ";
  std::cout << shape.getFrameRect().pos.y << ")";
  std::cout << std::endl;
}

void printShapeInfo(const styagov::Shape & shape)
{
  std::cout << "Area = " << shape.getArea() << "; ";
  std::cout << "Width = " << shape.getFrameRect().width << "; ";
  std::cout << "Height = " << shape.getFrameRect().height << ".";
  std::cout << std::endl;
  printShapeCoordinates(shape);
  std::cout << std::endl;
}

void moveShape(styagov::Shape & shape, const double x, const double y)
{
  shape.move({ x, y });
  std::cout << "Moving in (" << x << "; " << y << ")" << std::endl;
  printShapeInfo(shape);

  shape.move(x / 2.0, y / 2.0);
  std::cout << "Shifting by " << (x / 2.0) << " to right and by " << (y / 2.0) << " to top.";
  std::cout << std::endl;
  printShapeInfo(shape);
}

void scaleShape(styagov::Shape & shape, const double ratio)
{
  shape.scale(ratio);
  std::cout << "Scaling by " << ratio << "." << std::endl;
  printShapeInfo(shape);

  shape.scale(1.0 / ratio);
  std::cout << "Downscaling to default size." << std::endl;
  printShapeInfo(shape);
}

void rotateShape(styagov::Shape & shape, const double alpha)
{
    shape.rotate(alpha);
    std::cout << "Rotated by " << alpha << " degrees." << std::endl;
    printShapeInfo(shape);

    shape.rotate(-1 * alpha);
    std::cout << "Rotated back to the origin angle." << std::endl;
    printShapeInfo(shape);
}

void testShape(styagov::Shape & shape)
{
  printShapeInfo(shape);
  moveShape(shape, 10.0, 20.0);
  scaleShape(shape, 4.0);
  rotateShape(shape, 45.0);
}

int main() {
  std::shared_ptr <styagov::Shape> shapePtr = nullptr;

  try
  {
    styagov::Circle circle = Circle({ 7.0, 0.0 }, 5.0);
    styagov::Rectangle rectangle = Rectangle({ -5.0, 10.0 }, 15.0, 10.0);
    styagov::Triangle triangle = Triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 });

    shapePtr = std::make_shared <styagov::Circle>(circle);
    std::cout << "=== Testing Circle ===" << std::endl;
    testShape(* shapePtr);
    styagov::CompositeShape compositeShape(shapePtr);

    shapePtr = std::make_shared <styagov::Rectangle>(rectangle);
    compositeShape.add(shapePtr);
    std::cout << std::endl << "=== Testing Rectangle ===" << std::endl;
    testShape(* shapePtr);

    shapePtr = std::make_shared <styagov::Triangle>(triangle);
    compositeShape.add(shapePtr);
    std::cout << std::endl << "=== Testing Triangle ===" << std::endl;
    testShape(* shapePtr);

    // copy created composite shape
    styagov::CompositeShape copyCompositeShape(compositeShape); // size of copy composite shape = 3
    copyCompositeShape.clearShapes(); // removing all shapes because they're the same with compositeShape's shapes

    // creating new shapes for copyCompositeShape
    styagov::Circle newCircle = Circle({ 3.0, 3.0 }, 4.0);
    styagov::Rectangle newRectangle = Rectangle({ -5.0, -5.0 }, 2.0, 8.0);
    styagov::Triangle newTriangle = Triangle({ 0.0, 0.0 }, { 2.0, 4.0 }, { 4.0, 0.0 });
    // adding new shape to copyCompositeShape
    shapePtr = std::make_shared <styagov::Circle>(newCircle);
    copyCompositeShape.add(shapePtr);
    shapePtr = std::make_shared <styagov::Rectangle>(newRectangle);
    copyCompositeShape.add(shapePtr);
    shapePtr = std::make_shared <styagov::Triangle>(newTriangle);
    copyCompositeShape.add(shapePtr);
    // noew size of copy composite shape is back again 3

    // testing `+` operator overloading for CompositeShape class
    compositeShape = compositeShape + copyCompositeShape; // now compositeShape has 6 different shapes
    std::cout << "compositeShape size = " << compositeShape.getSize() << std::endl;

    std::cout << std::endl << "=== Testing Composite Shape ===" << std::endl;
    testShape(compositeShape);
    std::cout << "*** Removed Rectangle from Composite Shape ***" << std::endl;
    compositeShape.remove(1);
    testShape(compositeShape);
    std::cout << "*** Removing all remain shapes from Composite Shape ***" << std::endl;
    compositeShape.clearShapes();
    testShape(compositeShape);

    styagov::Circle matrixCircle { { 7.0, 0.0 }, 5.0 };
    styagov::Rectangle matrixRectangleA { { -5.0, 10.0 }, 15.0, 10.0 };
    styagov::Rectangle matrixRectangleB { { 0.0, 7.0 }, 10.0, 2.0 };
    styagov::Rectangle matrixRectangleC { { 12.0, -1.0 }, 13.0, 12.0 };
    styagov::Rectangle matrixRectangleD { { 2.5, 3.5 }, 5.0, 5.0 };

    std::shared_ptr <styagov::Shape> matrixCirclePtr = std::make_shared <styagov::Circle>(matrixCircle);
    std::shared_ptr <styagov::Shape> matrixRectangleAPtr = std::make_shared <styagov::Rectangle>(matrixRectangleA);
    std::shared_ptr <styagov::Shape> matrixRectangleBPtr = std::make_shared <styagov::Rectangle>(matrixRectangleB);
    std::shared_ptr <styagov::Shape> matrixRectangleCPtr = std::make_shared <styagov::Rectangle>(matrixRectangleC);
    std::shared_ptr <styagov::Shape> matrixRectangleDPtr = std::make_shared <styagov::Rectangle>(matrixRectangleD);

    styagov::Matrix matrix(matrixCirclePtr);
    matrix.add(matrixRectangleAPtr);
    matrix.add(matrixRectangleBPtr);
    matrix.add(matrixRectangleCPtr);
    matrix.add(matrixRectangleDPtr);

    std::cout << "=== Testing Matrix ===" << std::endl;
    std::unique_ptr <std::shared_ptr<styagov::Shape>[]> matrixLayerA = matrix[0];
    std::unique_ptr <std::shared_ptr<styagov::Shape>[]> matrixLayerB = matrix[1];
    std::unique_ptr <std::shared_ptr<styagov::Shape>[]> matrixLayerC = matrix[2];
 
    if(matrixLayerA[0] == matrixCirclePtr)
    {
      std::cout << "= Layer: 1; Element: 1 - Circle =" << std::endl;
      printShapeInfo(* matrixCirclePtr);
    }
    
    if (matrixLayerA[1] == matrixRectangleBPtr)
    {
      std::cout << "= Layer: 1; Element: 2 - Rectangle =" << std::endl;
      printShapeInfo(* matrixRectangleBPtr);
    }
    
    if (matrixLayerB[0] == matrixRectangleAPtr)
    {
      std::cout << "= Layer: 2; Element: 1 - Rectangle =" << std::endl;
      printShapeInfo(* matrixRectangleAPtr);
    }
    
    if (matrixLayerB[1] == matrixRectangleCPtr)
    {
      std::cout << "= Layer: 2; Element: 2 - Rectangle =" << std::endl;
      printShapeInfo(* matrixRectangleCPtr);
    }
    
    if (matrixLayerC[0] == matrixRectangleDPtr)
    {
      std::cout << "= Layer: 3; Element: 1 - Rectangle =" << std::endl;
      printShapeInfo(* matrixRectangleDPtr);
    }

    if (matrixLayerC[1] == nullptr)
    {
      std::cout << "= Layer: 3; Element: 2 - null =" << std::endl;
    }

    std::cout << std::endl << "= Testing Matrix from Composite Shape = " << std::endl;
    styagov::Matrix matrixFromCompositeShape(copyCompositeShape);
    std::cout << "Layers: " << matrixFromCompositeShape.getLayers();
    std::cout << "; Layer size: " << matrixFromCompositeShape.getLayerSize() << std::endl;
  }
  catch(const std::invalid_argument & exception)
  {
    std::cerr << exception.what() << std::endl;

    return 1;
  }
  catch(const std::bad_alloc & exception)
  {
    std::cerr << exception.what() << std::endl;

    return 2;
  }

  return 0;
}
