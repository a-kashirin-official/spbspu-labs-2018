#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

using namespace solovev;

void printInf( Shape & shape)
{
  std::cout<<"Area: "<<shape.getArea()<<std::endl;
  std::cout<<"Position of center: ("<<shape.getFrameRect().pos.x<<", "<<shape.getFrameRect().pos.y<<")"<<std::endl;
  std::cout<<"Width of rectangle frame: "<<shape.getFrameRect().width<<std::endl;
  std::cout<<"Height of rectangle frame: "<<shape.getFrameRect().height<<std::endl;
}

void printInfComposite (CompositeShape & shape)
{
  std::cout<<"Area: "<< shape.getArea() << std::endl;
  std::cout<<"Position of center: ("<<shape.getFrameRect().pos.x<<", "<<shape.getFrameRect().pos.y<<")"<<std::endl;
  std::cout<<"Width of rectangle frame: "<<shape.getFrameRect().width<<std::endl;
  std::cout<<"Height of rectangle frame: "<<shape.getFrameRect().height<<std::endl;
}

int main()
{
  std::shared_ptr<Shape> rect1 = std::make_shared<Rectangle>(Rectangle({-4.0, -4.0}, 3.0, 3.0));
  std::shared_ptr<Shape> rect2 = std::make_shared<Rectangle>(Rectangle({-1.0, -1.0}, 2.0, 2.0));
  std::shared_ptr<Shape> rect3 = std::make_shared<Rectangle>(Rectangle({1.0, 1.0}, 3.0, 3.0));

  CompositeShape compositeShape = CompositeShape();
  compositeShape.addShape(rect1);
  compositeShape.addShape(rect2);
  compositeShape.addShape(rect3);

  printInfComposite(compositeShape);

  compositeShape.move({1, 1});
  printInfComposite(compositeShape);

  compositeShape.move(9, 6);
  printInfComposite(compositeShape);

  compositeShape.rmShape(1);
  compositeShape.rmShape(0);

  printInfComposite(compositeShape);

  CompositeShape compositeShape2(rect2);
  compositeShape2.addShape(rect1);
  printInfComposite(compositeShape2);

  return 0;
}
