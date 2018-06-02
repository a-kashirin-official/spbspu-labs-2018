#include <iostream>
#include <memory>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace afanasiev;

void printInfo(const Shape & object)
{
  std::cout << "Area: " << object.getArea() << std::endl;
  const rectangle_t frame = object.getFrameRect();
  std::cout << "Frame for object:" << std::endl;
  std::cout << "\tMiddle of frame: " << frame.pos.x << ", " << frame.pos.y << std::endl;
  std::cout << "\tWidth of frame: " << frame.width << std::endl;
  std::cout << "\tHeight of frame: " << frame.height << std::endl;
}

int main()
{
  try
  {
    Circle circle1{ { -2.0, -2.0 }, 1.0 };
    std::shared_ptr<Shape> circlePtr1 = std::make_shared<Circle>(circle1);
    CompositeShape compositeShape(circlePtr1);
    std::cout << "Composite shape:" << std::endl;
    printInfo(compositeShape);
    compositeShape.rotate(90);
    printInfo(compositeShape);
    compositeShape.scale(2.0);
    printInfo(compositeShape);
    compositeShape.removeShape(1);
    printInfo(compositeShape);
    compositeShape.clear();
    printInfo(compositeShape);
    std::cout << std::endl;
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

