#include <iostream>
#include <memory>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"
#include "polygon.hpp"
#include "matrix.hpp"
#include "shape.hpp"


int main()
{
  try {

    turkin::Circle testCircle1(10.0, {-10.0, 0.0});
    turkin::Circle testCircle2(20.0, {40.0, 30.0});
    turkin::Rectangle testRectangle1(20.0, 40.0, {20.0, 30.0});
    turkin::Rectangle testRectangle2(20.0, 40.0, {30.0, 0.0});
    std::shared_ptr<turkin::Shape> circlePtr1 = std::make_shared<turkin::Circle>(testCircle1);
    std::shared_ptr<turkin::Shape> circlePtr2 = std::make_shared<turkin::Circle>(testCircle2);
    std::shared_ptr<turkin::Shape> rectanglePtr1 = std::make_shared<turkin::Rectangle>(testRectangle1);
    std::shared_ptr<turkin::Shape> rectanglePtr2 = std::make_shared<turkin::Rectangle>(testRectangle2);
    turkin::CompositeShape testCS(circlePtr1);
    testCS.add(rectanglePtr1);
    testCS.add(rectanglePtr2);
    size_t size = testCS.getSize();
    std::shared_ptr<turkin::CompositeShape> array = std::make_shared<turkin::CompositeShape>(testCS);
    turkin::Matrix mat(circlePtr2);
    mat.addFromShape(array, size);
    std::unique_ptr<std::shared_ptr<turkin::Shape>[]> layer0 = mat[0];
    std::unique_ptr<std::shared_ptr<turkin::Shape>[]> layer1 = mat[1];
    std::unique_ptr<std::shared_ptr<turkin::Shape>[]> layer2 = mat[2];

    std::cout<< layer0[0]->getFrameRect().pos.x << " " << layer0[0]->getFrameRect().pos.y << std::endl;
    std::cout<< layer0[1]->getFrameRect().pos.x << " " << layer0[1]->getFrameRect().pos.y << std::endl;
    std::cout<< layer1[0]->getFrameRect().pos.x << " " << layer1[0]->getFrameRect().pos.y << std::endl;
    std::cout<< layer2[0]->getFrameRect().pos.x << " " << layer2[0]->getFrameRect().pos.y << std::endl;
  }
  catch (std::exception &error) {
    std::cerr << error.what() << std::endl;
    return 1;
  }

  return 0;
}
