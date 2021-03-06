#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

using namespace starikov;

int main()
{
  Rectangle objRectangle({40.0,9.0,5.0,1.0});
  Circle objCircle(7.0,{4.0,2.0});
  std::cout << "Rectangle's area = " << objRectangle.getArea() << std::endl;
  objRectangle.move({32.0,43.0});
  std::cout << "New Rectangle's centre is (" << objRectangle.getFrameRect().pos.x << ";" << objRectangle.getFrameRect().pos.y << ")" << std::endl;
  objRectangle.move(12.0,33.0);
  std::cout << "New Rectangle's coordinates is (" << objRectangle.getFrameRect().pos.x << ";" << objRectangle.getFrameRect().pos.y << ")" << std::endl;
  objRectangle.scale(3.0);
  std::cout << "New Rectangles's height is " << objRectangle.getFrameRect().height << std::endl;
  std::cout << "New Rectangle's width is " << objRectangle.getFrameRect().width << std::endl;
  std::cout << "**************************************************************" << std::endl;
  std::cout << "Circle's area = " << objCircle.getArea() << std::endl;
  std::cout << "Rectangle from the Circle: " << "width = " << objCircle.getFrameRect().width << " height = " << objCircle.getFrameRect().height << std::endl;
  objCircle.move({12.0,15.0});
  std::cout << "New Circle's centre is (" << objCircle.getFrameRect().pos.x << ";" << objCircle.getFrameRect().pos.y << ")" << std::endl;
  objCircle.move(25.0,71.0);
  std::cout << "New Circle's coordinates is (" << objCircle.getFrameRect().pos.x << ";" << objCircle.getFrameRect().pos.y << ")" << std::endl;
  objCircle.scale(3.0);
  std::cout << "New Circle's radius is " << (objCircle.getFrameRect().height / 2) << std::endl;
  std::cout << "**************************************************************" << std::endl;
  Rectangle objScaleRectangle({40.0,9.0,5.0,1.0});
  Circle objScaleCircle(7.0,{8.0,23.0});
  std::shared_ptr <Shape> rectanglePtr = std::make_shared <Rectangle> (objScaleRectangle);
  std::shared_ptr <Shape> circlePtr = std::make_shared <Circle> (objScaleCircle);
  CompositeShape objComposite(rectanglePtr);
  objComposite.addShape(circlePtr);
  std::cout << "Composite shape's height = " << objComposite.getFrameRect().height << std::endl;
  std::cout << "Composite shape's width = " << objComposite.getFrameRect().width << std::endl;
  std::cout << "Composite shape's centre is (" << objComposite.getFrameRect().pos.x << ";" << objComposite.getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Composite's area = " << objComposite.getArea() << std::endl;
  objComposite.move({32.0,43.0});
  std::cout << "New Composite's centre is (" << objComposite.getShapeInfo().pos.x << ";" << objComposite.getShapeInfo().pos.y << ")" << std::endl;
  objComposite.move(12.0,33.0);
  std::cout << "New Composite's coordinates is (" << objComposite.getShapeInfo().pos.x << ";" << objComposite.getShapeInfo().pos.y << ")" << std::endl;
  objComposite.scale(3.0);
  std::cout << "New Composite's height is " << objComposite.getShapeInfo().height << std::endl;
  std::cout << "New Composite's width is " << objComposite.getShapeInfo().width << std::endl;
  return 0;
}
