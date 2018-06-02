#include <iostream>
#include <string>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"

using namespace tseptsov;

void OutDataShape(const Shape &shape)
{
  shape.OutData();
}

int main()
{

  try {
    tseptsov::Circle circle1(10.0, {-10.0, 0.0});
    tseptsov::Circle circle2(20.0, {40.0, 30.0});
    tseptsov::Circle circle3(30.0, {50.0, 40.0});
    tseptsov::Rectangle rectangle1(20.0, 40.0, {20.0, 30.0});
    tseptsov::Rectangle rectangle2(20.0, 40.0, {30.0, 0.0});
    std::shared_ptr < tseptsov::Shape > circlePtr1 = std::make_shared < tseptsov::Circle >(circle1);
    std::shared_ptr < tseptsov::Shape > circlePtr2 = std::make_shared < tseptsov::Circle >(circle2);
    std::shared_ptr < tseptsov::Shape > circlePtr3 = std::make_shared < tseptsov::Circle >(circle3);
    std::shared_ptr < tseptsov::Shape > rectanglePtr1 = std::make_shared < tseptsov::Rectangle >(rectangle1);
    std::shared_ptr < tseptsov::Shape > rectanglePtr2 = std::make_shared < tseptsov::Rectangle >(rectangle2);
    tseptsov::CompositeShape compositeshape(circlePtr2);
    compositeshape.add(circlePtr3);
    compositeshape.add(rectanglePtr1);
    compositeshape.add(rectanglePtr2);
    size_t size = compositeshape.getSize();
    std::shared_ptr < tseptsov::CompositeShape > array = std::make_shared < tseptsov::CompositeShape >(compositeshape);
    tseptsov::Matrix matrix(circlePtr1);
    matrix.addFromCShape(array, size);
    std::unique_ptr < std::shared_ptr < tseptsov::Shape >[] > layer0 = matrix[0];
    std::unique_ptr < std::shared_ptr < tseptsov::Shape >[] > layer1 = matrix[1];
    std::unique_ptr < std::shared_ptr < tseptsov::Shape >[] > layer2 = matrix[2];
    std::unique_ptr < std::shared_ptr < tseptsov::Shape >[] > layer3 = matrix[3];

    std::cout << "Width = " << layer0[0]->getFrameRect().width << std::endl;
    std::cout << "Height = " << layer0[0]->getFrameRect().height << std::endl;
    std::cout << "X = " << layer0[0]->getFrameRect().pos.x << " " << "Y = " << layer0[0]->getFrameRect().pos.y
              << std::endl;
    std::cout << std::endl;
    std::cout << "Width = " << layer0[1]->getFrameRect().width << std::endl;
    std::cout << "Height = " << layer0[1]->getFrameRect().height << std::endl;
    std::cout << "X = " << layer0[1]->getFrameRect().pos.x << " " << "Y = " << layer0[1]->getFrameRect().pos.y
              << std::endl;
    std::cout << std::endl;
    std::cout << "Width = " << layer1[0]->getFrameRect().width << std::endl;
    std::cout << "Height = " << layer1[0]->getFrameRect().height << std::endl;
    std::cout << "X = " << layer1[0]->getFrameRect().pos.x << " " << "Y = " << layer1[0]->getFrameRect().pos.y
              << std::endl;
    std::cout << std::endl;
    std::cout << "Width = " << layer2[0]->getFrameRect().width << std::endl;
    std::cout << "Height = " << layer2[0]->getFrameRect().height << std::endl;
    std::cout << "X = " << layer2[0]->getFrameRect().pos.x << " " << "Y = " << layer2[0]->getFrameRect().pos.y
              << std::endl;
    std::cout << std::endl;
    std::cout << "Width = " << layer3[0]->getFrameRect().width << std::endl;
    std::cout << "Height = " << layer3[0]->getFrameRect().height << std::endl;
    std::cout << "X = " << layer3[0]->getFrameRect().pos.x << " " << "Y = " << layer3[0]->getFrameRect().pos.y
              << std::endl;


  }
  catch (std::invalid_argument &error) {
    std::cerr << error.what() << std::endl;
    return 1;
  }

  return 0;
}

