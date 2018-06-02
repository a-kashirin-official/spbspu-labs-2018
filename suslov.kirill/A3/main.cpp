#include <iostream>

#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

void showInfo(const suslov::Shape & shape)
{
  std::cout << "Width of the frame:\t";
  std::cout << shape.getFrameRect().width << std::endl;
  std::cout << "Height of the frame:\t";
  std::cout << shape.getFrameRect().height << std::endl;
  std::cout << "Center of the frame\t(" << shape.getFrameRect().pos.x << ", "
  << shape.getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Sum of the areas:\t";
  std::cout << shape.getArea() << std::endl << std::endl;
 }

int main()
{
  suslov::Rectangle rect({2.0, 2.0}, 2.0, 2.0);
  suslov::Rectangle rect2({6.0, 4.0}, 2.0, 2.0);
  std::shared_ptr < suslov::Shape > pRect = std::make_shared < suslov::Rectangle > (rect);
  std::shared_ptr < suslov::Shape > pRect2 = std::make_shared < suslov::Rectangle > (rect2);
  suslov::CompositeShape compositeShape(pRect);


  std::cout << "First shape (Rectangle): " << std::endl;
  showInfo(rect);

  std::cout << "Second shape (Rectangle): " << std::endl;
  showInfo(rect2);

  std::cout << "=======================================" << std::endl << std::endl;
  std::cout << "Composite shape with first shape:" << std::endl << std::endl;
  showInfo(compositeShape);
  std::cout << "Second shape was added:" << std::endl << std::endl;
  compositeShape.addShape(pRect2);
  showInfo(compositeShape);
  std::cout << "Scale(3.0)" << std::endl << std::endl;
  compositeShape.scale(3.0);
  showInfo(compositeShape);
  std::cout << "Move composite shape to (25, 40)" << std::endl << std::endl;
  compositeShape.move({25.0, 40.0});
  showInfo(compositeShape);
  std::cout << "Delete shape (1)" << std::endl << std::endl;
  compositeShape.deleteShape(1);
  showInfo(compositeShape);
  std::cout << "Delete all shapes" << std::endl << std::endl;
  compositeShape.deleteAllShapes();
  showInfo(compositeShape);
  return 0;
}
