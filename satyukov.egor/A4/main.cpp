#include <iostream>
#include <memory>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"


void printInfo(const std::shared_ptr < satyukov:: Shape > shape)
{
  std::cout << "Area:" << shape->getArea() << std::endl;
  std::cout << "Angle:" << shape->getAngle() << std::endl;
  const satyukov::rectangle_t testFrameRect = shape->getFrameRect();
  std::cout << "Get frame rectangle:" << std::endl;
  std::cout << "Center:" << "(" << testFrameRect.pos.x << " ; " << testFrameRect.pos.y << ")" << std::endl;
  std::cout << "Width, height:" << testFrameRect.width << ", " << testFrameRect.height << std::endl << std::endl;
}

void printInfo(const satyukov::Shape & shape)
{
  std::cout << "Area:" << shape.getArea() << std::endl;
  std::cout << "Angle:" << shape.getAngle() << std::endl;
  const satyukov::rectangle_t testFrameRect = shape.getFrameRect();
  std::cout << "Get frame rectangle:" << std::endl;
  std::cout << "Center:" << "(" << testFrameRect.pos.x << " ; " << testFrameRect.pos.y << ")" << std::endl;
  std::cout << "Width, height:" << testFrameRect.width << ", " << testFrameRect.height << std::endl << std::endl;
}

int main()
{
  try
  {
    satyukov::Circle testCircle ({ 20.0, 0.0 }, 10.0);
    std::cout << "Сirlce before rotation:" << std::endl;
    printInfo(testCircle);
    testCircle.rotate(90);
    std::cout << "Сirlce after rotation (90 degrees):" << std::endl;
    printInfo(testCircle);

    satyukov::Rectangle testRectangle ({ 0.0, 0.0 }, 40.0, 20.0);
    std::cout << "Rectangle before rotation:" << std::endl;
    printInfo(testRectangle);
    testRectangle.rotate(90);
    std::cout << "Rectangle after rotation (90 degrees):" << std::endl;
    printInfo(testRectangle);

    std::shared_ptr < satyukov::Shape > circlePtr = std::make_shared < satyukov::Circle > (testCircle);
    std::shared_ptr < satyukov::Shape > rectanglePtr = std::make_shared < satyukov::Rectangle > (testRectangle);

    satyukov::CompositeShape testCompositeShape(circlePtr);
    std::cout << "Composite Shape = Circle:" << std::endl;
    printInfo(testCompositeShape);
    testCompositeShape.addShape(rectanglePtr);
    std::cout << "Composite Shape = Circle + Rectangle:" << std::endl;
    printInfo(testCompositeShape);
    testCompositeShape.rotate(90);
    std::cout << "Composite Shape after rotation (90 degrees):" << std::endl;
    printInfo(testCompositeShape);
    std::cout << "Circle:" << std::endl;
    printInfo(testCompositeShape.getShape(0));
    std::cout << "Rectangle:" << std::endl;
    printInfo(testCompositeShape.getShape(1));

    satyukov::Circle testCircleM1 ({ -10.0, 0.0 }, 10.0);
    satyukov::Circle testCircleM2 ({ 40.0, 30.0 }, 20.0);
    satyukov::Rectangle testRectangleM1 ({ 20.0, 30.0 }, 20.0, 40.0);
    satyukov::Rectangle testRectangleM2 ({ 30.0, 0.0 }, 20.0, 40.0);

    std::shared_ptr < satyukov::Shape > circlePtrM1 = std::make_shared < satyukov::Circle > (testCircleM1);
    std::shared_ptr < satyukov::Shape > circlePtrM2 = std::make_shared < satyukov::Circle > (testCircleM2);
    std::shared_ptr < satyukov::Shape > rectanglePtrM1 = std::make_shared < satyukov::Rectangle > (testRectangleM1);
    std::shared_ptr < satyukov::Shape > rectanglePtrM2 = std::make_shared < satyukov::Rectangle > (testRectangleM2);

    satyukov::Matrix testMatrix(circlePtrM1);
    testMatrix.addShape(rectanglePtrM1);
    testMatrix.addShape(rectanglePtrM2);
    testMatrix.addShape(circlePtrM2);

    std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > layer0 = testMatrix[0];
    std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > layer1 = testMatrix[1];
    std::unique_ptr < std::shared_ptr < satyukov::Shape >[] > layer2 = testMatrix[2];
    
    std::cout << "Matrix" << std::endl;

    if (layer0[0] == circlePtrM1)
    {
      std::cout << "Layer 0, element 0 - circle 1" << std::endl;
    }
    if (layer0[1] == rectanglePtrM1)
    {
      std::cout << "Layer 0, element 1 - rectangle 1" << std::endl;
    }
    if (layer1[0] == rectanglePtrM2)
    {
      std::cout << "Layer 1, element 0 - rectangle 2" << std::endl;
    }
    if (layer1[1] == nullptr)
    {
      std::cout << "Layer 1, element 1 - nullptr" << std::endl;
    }
    if (layer2[0] == circlePtrM2)
    {
      std::cout << "Layer 2, element 0 - circle 2" << std::endl;
    }
    if (layer2[1] == nullptr)
    {
      std::cout << "Layer 2, element 1 - nullptr" << std::endl;
    }
  }
  catch(std::invalid_argument & e)
  {
    std::cerr << e.what() << std::endl;
  }
  catch(std::out_of_range & e)
  {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}
