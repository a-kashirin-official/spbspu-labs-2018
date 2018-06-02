#include <iostream>
#include <memory>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"


int main()
{
  try {
    turkin::Rectangle rectangle(1.0, 1.0, {1.5, 1.5});
    turkin::Circle circle(7.15, {2.0, 7.5});
    turkin::Triangle triangle({3.5, 6.0}, {9.7, 6.5}, {2.5, 4.5});

    std::shared_ptr<turkin::Shape> circlePtr = std::make_shared<turkin::Circle>(circle);
    std::shared_ptr<turkin::Shape> rectanglePtr = std::make_shared<turkin::Rectangle>(rectangle);
    std::shared_ptr<turkin::Shape> trianglePtr = std::make_shared<turkin::Triangle>(triangle);
    std::cout << "Add circle, rectangle, triangle..." << std::endl;
    turkin::CompositeShape testCompositeShape(circlePtr);
    testCompositeShape.add(rectanglePtr);
    testCompositeShape.add(trianglePtr);
    std::cout << "Area:" << std::endl;
    std::cout << testCompositeShape.getArea() << std::endl;
    std::cout << "Width: " << testCompositeShape.getFrameRect().width << " Height: "
              << testCompositeShape.getFrameRect().height << std::endl;
    std::cout << "Pos(x): " << testCompositeShape.getFrameRect().pos.x << " Pos(y): "
              << testCompositeShape.getFrameRect().pos.y << std::endl;

    std::cout << "--------------------" << std::endl;
    std::cout << "Scale(5) and move(1,1)..." << std::endl;
    testCompositeShape.scale(5);
    testCompositeShape.move(1, 1);
    std::cout << "Area:" << std::endl;
    std::cout << testCompositeShape.getArea() << std::endl;
    std::cout << "Width: " << testCompositeShape.getFrameRect().width << " Height: "
              << testCompositeShape.getFrameRect().height << std::endl;
    std::cout << "Pos(x): " << testCompositeShape.getFrameRect().pos.x << " Pos(y): "
              << testCompositeShape.getFrameRect().pos.y << std::endl;


    std::cout << "--------------------" << std::endl;
    std::cout << "Delete circle..." << std::endl;
    testCompositeShape.del(0);
    std::cout << "Area:" << std::endl;
    std::cout << testCompositeShape.getArea() << std::endl;
    std::cout << "Width: " << testCompositeShape.getFrameRect().width << " Height: "
              << testCompositeShape.getFrameRect().height << std::endl;
    std::cout << "Pos(x): " << testCompositeShape.getFrameRect().pos.x << " Pos(y): "
              << testCompositeShape.getFrameRect().pos.y << std::endl;
  }
  catch (std::exception &error) {
    std::cerr << error.what() << std::endl;
    return 1;
  }

  return 0;
}
