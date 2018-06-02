#include <iostream>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
using namespace konkin;

int main()
{
  try
  {
    konkin::point_t p1 = {4.0, 4.0};
    konkin::point_t p2 = {2.0, 2.0};
    konkin::Rectangle rect({1.0, 1.0, p1});
    konkin::Circle circle(p2, 1.0);

    konkin::Shape * pointer = &rect;

    std::cout << "Rectangle demo" << std::endl;
    std::cout << "Coordinates X = " << pointer -> getFrameRect().pos.x << " Y = "
              << pointer -> getFrameRect().pos.y << std::endl;
    std::cout << "Width = " << pointer -> getFrameRect().width << std::endl;
    std::cout << "Height = " << pointer -> getFrameRect().height << std::endl;
    std::cout << "Area = " << pointer -> getArea() << std::endl;
    std::cout << "Scaling of rectangle. Coefficient = 10" << std::endl;
    pointer -> scale(10);
    std::cout << "New width = " << pointer -> getFrameRect().width << std::endl;
    std::cout << "New height = " << pointer -> getFrameRect().height << std::endl;
    std::cout << "New area = " << pointer -> getArea() << std::endl;

    std::cout << "Move for (dx = 50.0, dy = 100.0)" << std::endl;
    pointer ->move(50.0, 100.0);
    std::cout << "New coordinates:" <<std::endl;
    std::cout << "Coordinates X = " << pointer -> getFrameRect().pos.x << " Y = "
              << pointer -> getFrameRect().pos.y << std::endl;
    std::cout << std::endl;

    pointer = &circle;

    std::cout << "Circle demo" << std::endl;
    std::cout << "Coordinates X = " << pointer -> getFrameRect().pos.x << " Y = "
              << pointer -> getFrameRect().pos.y << std::endl;
    std::cout << "Height = " << pointer -> getFrameRect().height << std::endl;
    std::cout << "Width = " << pointer -> getFrameRect().width << std::endl;
    std::cout << "Area = " << pointer ->getArea() << std::endl;
    std::cout << "Scaling of circle. Coefficient = 5" << std::endl;
    pointer -> scale(5);
    std::cout << "New width = " << pointer -> getFrameRect().width << std::endl;
    std::cout << "New height = " << pointer -> getFrameRect().height << std::endl;
    std::cout << "New area = " << pointer -> getArea() << std::endl;

    std::cout << "Move to point (100.0, 100.0)" << std::endl;
    pointer -> move({100.0, 100.0});
    std::cout << "New coordinates:" <<std::endl;
    std::cout << "Coordinates X = " << pointer -> getFrameRect().pos.x << " Y = "
              << pointer -> getFrameRect().pos.y << std::endl;
    std::cout << std::endl;

    std::cout << "CompositeShape demo" <<std::endl;

    konkin::CompositeShape comp_shape;
    konkin::CompositeShape::ptr_type rectPtr = std::make_shared<konkin::Rectangle>(rect);
    konkin::CompositeShape::ptr_type circPtr = std::make_shared<konkin::Circle>(circle);

    std::cout << "add rectangle" <<std::endl;
    comp_shape.addShape(rectPtr);
    std::cout <<"amount of shapes ="<< comp_shape.size() << std::endl;
    std::cout << comp_shape.getFrameRect().pos.x << ' '<< comp_shape.getFrameRect().pos.y << std::endl;

    std::cout << "add circle" <<std::endl;
    comp_shape.addShape(circPtr);
    std::cout <<"amount of shapes ="<< comp_shape.size() << std::endl;
    std::cout << comp_shape.getFrameRect().pos.x << ' '<< comp_shape.getFrameRect().pos.y << std::endl;

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
    comp_shape.move({-3.0, -3.0});
    std::cout << "X1 = " <<comp_shape.getFrameRect().pos.x << ' ';
    std::cout << "Y1 = " <<comp_shape.getFrameRect().pos.y << std::endl;


    std::cout << "Moving by dx = 3, dy = 3" <<std::endl;
    comp_shape.move(3.0, 3.0);
    std::cout << "X2 = " <<comp_shape.getFrameRect().pos.x << ' ';
    std::cout << "Y2 = " <<comp_shape.getFrameRect().pos.y <<std::endl;

    std::cout << "remove 1-st shape" <<std::endl;
    comp_shape.removeShape(1);
    std::cout <<"amount of shapes ="<< comp_shape.size() << std::endl;
    std::cout << "X2 = " <<comp_shape.getFrameRect().pos.x << ' ';
    std::cout << "Y2 = " <<comp_shape.getFrameRect().pos.y <<std::endl;
  }
  catch (std::invalid_argument & error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
    return 0;
}
