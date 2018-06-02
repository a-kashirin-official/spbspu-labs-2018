#include <iostream>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace stashevskii;

void print(const CompositeShape & shapes_)
{
  const rectangle_t obj = shapes_.getFrameRect();
  std::cout << "Width: " << obj.width << " Height: " << obj.height<< std::endl;
  std::cout << "X: " << obj.pos.x << " Y: " << obj.pos.y << std::endl;
  std::cout << "Area:" << shapes_.getArea() << std::endl;
  std::cout << std::endl;
}


int main()
{
  CompositeShape objshapes_;
  objshapes_.addShape(std::shared_ptr< Shape > (new Rectangle {10, 10, {5, 5}}));
  objshapes_.addShape(std::shared_ptr< Shape > (new Circle {10, {5, 5}}));
  print(objshapes_);

  CompositeShape objshapes_2;
  objshapes_.addShape(std::shared_ptr< Shape > (new Rectangle {100, 100, {50, 50}}));
  objshapes_.addShape(std::shared_ptr< Shape > (new Circle {100, {50, 50}}));
  print(objshapes_);

  CompositeShape objshapes_3(objshapes_);
  objshapes_2 = std::move(objshapes_);
  objshapes_3.deleteShape(1);
  print(objshapes_3);

  objshapes_.deleteAll();
  objshapes_2.deleteAll();
  objshapes_3.deleteAll();
  print(objshapes_3);

  return 0;
}
