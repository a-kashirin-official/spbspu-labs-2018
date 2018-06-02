#include <iostream>
#include <memory>

#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

using namespace hvetsckovich;

void printShapeInfo(const Shape & shape)
{
  std::cout << "Shape Info: " << "Area = " << shape.getArea() << ", ";
  std::cout << "Width = " << shape.getFrameRect().width << ", ";
  std::cout << "Height = " << shape.getFrameRect().height << "."  << std::endl;
}

void printShapeCoordinates(const Shape & shape)
{
  std::cout << "Center (" << shape.getPos().x << "; ";
  std::cout << shape.getPos().y << ")"  << std::endl;
}

void moveShape(Shape & shape, const double x, const double y)
{
  shape.move({ x, y });
}

void scaleShape(Shape & shape, const double ratio)
{
  shape.scale(ratio);
}

void testShape(Shape & shape)
{
  printShapeCoordinates(shape);
  moveShape (shape, -5.0, 10.0);
  std::cout << "Moved shape: ";
  printShapeInfo(shape);
  printShapeCoordinates(shape);

  scaleShape(shape, 2.0);
  std::cout << "Scaled shape: ";
  printShapeInfo(shape);
  printShapeCoordinates(shape);
}

int main() {
  std::shared_ptr< Shape > shape = nullptr;

  try
  {
    Circle circle = Circle ({ 7.0, 0.0 }, 5.0);
    Rectangle rectangle = Rectangle ({ -5.0, 10.0 }, 15.0, 10.0 );
    Triangle triangle = Triangle ({ 0.0, 0.0 }, { 3.0, 6.0 }, { 6.0, 0.0 });
    Triangle triangleCopyConstructor = Triangle(triangle);
    Triangle triangleAssignedCopy = triangle;

    shape = std::make_shared< Circle >(circle);
    std::cout << "Circle" << std::endl;
    printShapeInfo(* shape);
    testShape(* shape);
    CompositeShape compositeShape(shape);

    shape = std::make_shared< Rectangle >(rectangle);
    compositeShape.addShape(shape);
    std::cout << std::endl << "Rectangle" << std::endl;
    printShapeInfo(* shape);
    testShape(* shape);

    shape = std::make_shared< Triangle >(triangle);
    compositeShape.addShape(shape);
    std::cout << std::endl << "Triangle" << std::endl;
    printShapeInfo(* shape);
    testShape(* shape);

    std::cout << std::endl << "Composite Shape" << std::endl;
    printShapeInfo(compositeShape);
    testShape(compositeShape);
    std::cout << "Delete Triangle from Composite Shape" << std::endl;
    compositeShape.deleteShape(2);
    printShapeInfo(compositeShape);
    testShape(compositeShape);
    std::cout << "Clearing composite shape" << std::endl;
    compositeShape.deleteAllShapes();
    printShapeInfo(compositeShape);
    testShape(compositeShape);
    std::cout << "Adding triangle copy to composite shape" << std::endl;
    shape = std::make_shared< Triangle >(triangleCopyConstructor);
    compositeShape.addShape(shape);
    printShapeInfo(compositeShape);
    testShape(compositeShape);

    Circle mCircle = Circle({ 5.0, 2.0 }, 5.0);
    Rectangle mRect1 = Rectangle({ -15.0, 10.0 }, 15.0, 10.0);
    Rectangle mRect2 = Rectangle({ 4.0, 7.0 }, 10.0, 2.0);
    Rectangle mRect3 = Rectangle({ 12.0, -4.0 }, 13.0, 12.0);

    std::shared_ptr <Shape> mCirclePtr = std::make_shared <Circle>(mCircle);
    std::shared_ptr <Shape> mRect1Ptr = std::make_shared <Rectangle>(mRect1);
    std::shared_ptr <Shape> mRect2Ptr = std::make_shared <Rectangle>(mRect2);
    std::shared_ptr <Shape> mRect3Ptr = std::make_shared <Rectangle>(mRect3);
    
    Matrix matrix(mCirclePtr);
    matrix.addShape(mRect1Ptr);
    matrix.addShape(mRect2Ptr);
    matrix.addShape(mRect3Ptr);

    std::cout << "Matrix" << std::endl;
    std::unique_ptr <std::shared_ptr<Shape>[]> layer0 = matrix[0]; // [] operator for matrix
    std::unique_ptr <std::shared_ptr<Shape>[]> layer1 = matrix[1];
 
    if(layer0[0] == mCirclePtr)
    {
      std::cout << "* [0][0]. Circle" << std::endl;
      printShapeInfo(* mCirclePtr);
      printShapeCoordinates(* mCirclePtr);
    }
    if (layer0[1] == mRect1Ptr)
    {
      std::cout << "* [0][1]. Rectangle" << std::endl;
      printShapeInfo(* mRect1Ptr);
      printShapeCoordinates(* mRect1Ptr);
    }
    if (layer1[0] == mRect2Ptr)
    {
      std::cout << "* [1][0]. Rectangle" << std::endl;
      printShapeInfo(* mRect2Ptr);
      printShapeCoordinates(* mRect2Ptr);
    }
    if (layer1[1] == mRect3Ptr)
    {
      std::cout << "* [1][1]. Rectangle" << std::endl;
      printShapeInfo(* mRect3Ptr);
      printShapeCoordinates(* mRect3Ptr);
    }
  }
  catch(const std::bad_alloc & exception)
  {
    std::cerr << exception.what() << std::endl;
    return 1;
  }
  catch(const std::invalid_argument & exception)
  {
    std::cout << exception.what() << std::endl;
    return 2;
  }

  return 0;
}
