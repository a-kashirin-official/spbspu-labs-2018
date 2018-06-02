#include <iostream>
#include <memory>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace shumkovskaya;

int main()
{
  Rectangle rect (10.0, 20.0, { 0.0, 0.0 });
  Circle cir (10.0, { 15.0, 0.0 });
  std::shared_ptr <Shape> rectanglePtr = std::make_shared <Rectangle> (rect);
  std::cout << "Rectangle width = " << rect.getFrameRect().width << std::endl;
  std::cout << "Rectangle height = " << rect.getFrameRect().height << std::endl;
  std::cout << "Rectangle center = (" << rect.getFrameRect().pos.x ;
  std::cout << ", " << rect.getFrameRect().pos.y << ")" << std::endl;
  std::shared_ptr <Shape> circlePtr = std::make_shared <Circle> (cir);
  std::cout << "Circle radius = " << cir.getFrameRect().width/2<< std::endl;
  std::cout << "Circle center = (" << cir.getFrameRect().pos.x ;
  std::cout << ", " << cir.getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Create composite shape" << std::endl;
  CompositeShape shapes(rectanglePtr);
  std::cout << "Frame rectangle width = " << shapes.getFrameRect().width << std::endl;
  std::cout << "Frame rectangle height = " << shapes.getFrameRect().height << std::endl;
  std::cout << "Frame rectangle center = (" << shapes.getFrameRect().pos.x ;
  std::cout << ", " << shapes.getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Amount of shapes = " << shapes.getAmount() << std::endl;
  std::cout << "Add circle" << std::endl;
  shapes.addShape(circlePtr);
  std::cout << "Frame rectangle width = " << shapes.getFrameRect().width << std::endl;
  std::cout << "Frame rectangle height = " << shapes.getFrameRect().height << std::endl;
  std::cout << "Frame rectangle center = (" << shapes.getFrameRect().pos.x ;
  std::cout << ", " << shapes.getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Amount of shapes = " << shapes.getAmount() << std::endl;
  shapes.scale(0.5);
  std::cout << "Composite shape after scaling on 0.5:" << std::endl;
  std::cout << "Frame rectangle width = " << shapes.getFrameRect().width << std::endl;
  std::cout << "Frame rectangle height = " << shapes.getFrameRect().height << std::endl;
  std::cout << "Frame rectangle center = (" << shapes.getFrameRect().pos.x ;
  std::cout << ", " << shapes.getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Amount of shapes = " << shapes.getAmount() << std::endl;
  std::cout << "Rectangle  after scaling composite shape:" << std::endl;
  std::cout << "Rectangle width = " << rect.getFrameRect().width << std::endl;
  std::cout << "Rectangle height = " << rect.getFrameRect().height << std::endl;
  std::cout << "Rectangle center = (" << rect.getFrameRect().pos.x ;
  std::cout << ", " << rect.getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Circle after scaling composite shape:" << std::endl;
  std::cout << "Circle radius = " << cir.getFrameRect().width/2<< std::endl;
  std::cout << "Circle center = (" << cir.getFrameRect().pos.x ;
  std::cout << ", " << cir.getFrameRect().pos.y << ")" << std::endl;
  shapes.move({50.0, 60.0});
  std::cout << "Composite shape after moving to {50, 60}:" << std::endl;
  std::cout << "Frame rectangle width = " << shapes.getFrameRect().width << std::endl;
  std::cout << "Frame rectangle height = " << shapes.getFrameRect().height << std::endl;
  std::cout << "Frame rectangle center = (" << shapes.getFrameRect().pos.x ;
  std::cout << ", " << shapes.getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Amount of shapes = " << shapes.getAmount() << std::endl;
  std::cout << "Rectangle after after moving composite shape:" << std::endl;
  std::cout << "Rectangle width = " << rect.getFrameRect().width << std::endl;
  std::cout << "Rectangle height = " << rect.getFrameRect().height << std::endl;
  std::cout << "Rectangle center = (" << rect.getFrameRect().pos.x ;
  std::cout << ", " << rect.getFrameRect().pos.y << ")" << std::endl;
  std::cout << "Circle after  after after moving composite shape:" << std::endl;
  std::cout << "Circle radius = " << cir.getFrameRect().width/2<< std::endl;
  std::cout << "Circle center = (" << cir.getFrameRect().pos.x ;
  std::cout << ", " << cir.getFrameRect().pos.y << ")" << std::endl;
  shapes.removeShape(1);
  std::cout << "Shapes' amount after removing circle:" << shapes.getAmount() << std::endl;
  return 0;
}

