#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "shape.hpp"

using namespace ivanov;

void printInfo(const Shape & anyShape)
{
  std::cout << anyShape.getFrameRect().pos.x << std::endl;
  std::cout << anyShape.getFrameRect().pos.y << std::endl;
  std::cout << anyShape.getArea() << std::endl;
}

int main()
{
  Rectangle shapeRect_({4.1, 20.0, {3.4, 4.2}});
  std::cout << shapeRect_.getArea() << std::endl;
  std::cout << shapeRect_.getFrameRect().pos.x << " " << shapeRect_.getFrameRect().pos.y << std::endl;
  shapeRect_.move(3.7, 5.5);
  std::cout << shapeRect_.getFrameRect().pos.x << " " << shapeRect_.getFrameRect().pos.y << std::endl;
  shapeRect_.move({2.1, 3.56});
  std::cout << shapeRect_.getFrameRect().pos.x << " " << shapeRect_.getFrameRect().pos.y << std::endl;
  shapeRect_.scale(7.9);
  std::cout << shapeRect_.getArea() << std::endl;

  Circle shapeCircle_({3.9, 4.12}, 4.0);
  std::cout << shapeCircle_.getArea() << std::endl;
  std::cout << shapeCircle_.getFrameRect().pos.x << " " << shapeCircle_.getFrameRect().pos.y << std::endl;
  shapeCircle_.move(3.3, 5.23);
  std::cout << shapeCircle_.getFrameRect().pos.x << " " << shapeCircle_.getFrameRect().pos.y << std::endl;
  shapeCircle_.move({14.12, 16.0});
  std::cout << shapeCircle_.getFrameRect().pos.x << " " << shapeCircle_.getFrameRect().pos.y << std::endl;
  shapeCircle_.scale(9.7);
  std::cout << shapeCircle_.getArea() << std::endl;


  printInfo(shapeRect_);
  printInfo(shapeCircle_);



  return 0;
}
