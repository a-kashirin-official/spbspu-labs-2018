#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

int main()
{
  shapiev::point_t p1 = {4.0, 4.0};
  shapiev::point_t p2 = {2.0, 2.0};
  shapiev::Rectangle rect(1.0, 1.0, p1);
  shapiev::Circle circle(p2, 1.0);

  shapiev::CompositeShape comp_shape;
  shapiev::CompositeShape::ptr_type rectPtr = std::make_shared<shapiev::Rectangle>(rect);
  shapiev::CompositeShape::ptr_type circPtr = std::make_shared<shapiev::Circle>(circle);

  std::cout << "add rectangle" <<std::endl;
  comp_shape.addShape(rectPtr);
  std::cout <<"shape0 ="<< comp_shape.size() << std::endl;
  std::cout << comp_shape.getFrameRect().pos.x << ' '<< comp_shape.getFrameRect().pos.y;

  std::cout << "add circle" <<std::endl;
  comp_shape.addShape(circPtr);
  std::cout <<"shape0 ="<< comp_shape.size() << std::endl;

  std::cout << "Area of CompositeShape is = " << comp_shape.getArea() <<std::endl;
  std::cout << "FrameRect of CompositeShape is:" << std::endl;
  std::cout << "X = " <<comp_shape.getFrameRect().pos.x << ' ';
  std::cout << "Y = " <<comp_shape.getFrameRect().pos.y <<std::endl;

  std::cout << "Width of CompositeShape = " <<comp_shape.getFrameRect().width<<std::endl;
  std::cout << "Height of CompositeShape = " <<comp_shape.getFrameRect().height<<std::endl;


  std::cout << "Scaling. Coef = 2" <<std::endl;
  comp_shape.scale(2.0);
  std::cout << "New parameters of CompositeShape" << std::endl;
  std::cout << "New area of CompositeShape is = " << comp_shape.getArea() << std::endl;
  std::cout << "New width of CompositeShape = " <<comp_shape.getFrameRect().width << std::endl;
  std::cout << "New height of CompositeShape = " <<comp_shape.getFrameRect().height << std::endl;


  std::cout << "Moving to point (-3.0 ; -3.0)" << std::endl;

  std::cout << "X1 = " <<comp_shape.getFrameRect().pos.x << ' ';
  std::cout << "Y1 = " <<comp_shape.getFrameRect().pos.y << std::endl;
  comp_shape.move({-3.0, -3.0});
  std::cout << "X1 = " <<comp_shape.getFrameRect().pos.x << ' ';
  std::cout << "Y1 = " <<comp_shape.getFrameRect().pos.y << std::endl;


  std::cout << "Moving by dx = 3, dy = 3" <<std::endl;
  comp_shape.move(3.0, 3.0);
  std::cout<<circle.getFrameRect().pos.x<< ' '<< circle.getFrameRect().pos.y<< std::endl;
  std::cout << "X2 = " <<comp_shape.getFrameRect().pos.x << ' ';
  std::cout << "Y2 = " <<comp_shape.getFrameRect().pos.y <<std::endl;



  std::cout << "remove 1-st shape" <<std::endl;
  comp_shape.removeShape(1);
  std::cout <<"shape0 ="<< comp_shape.size() << std::endl;

  std::cout << "" <<std::endl;

  return 0;
}
