#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "shape.hpp"

void printInfo(const Shape & anyShape)
{
  std::cout << anyShape.getFrameRect().pos.x << std::endl;
  std::cout << anyShape.getFrameRect().pos.y << std::endl;
  std::cout << anyShape.getArea() << std::endl;
}

int main()
{
  Rectangle shapeRect_({4, 20, {3, 4}});
  std::cout << shapeRect_.getArea() << std::endl;
  std::cout << shapeRect_.getFrameRect().pos.x << " " << shapeRect_.getFrameRect().pos.y << std::endl;
  shapeRect_.move(3, 5);
  std::cout << shapeRect_.getFrameRect().pos.x << " " << shapeRect_.getFrameRect().pos.y << std::endl;
  shapeRect_.move({2, 3.56});
  std::cout << shapeRect_.getFrameRect().pos.x << " " << shapeRect_.getFrameRect().pos.y << std::endl;

  Circle shapeCircle_({3, 4}, 4);
  std::cout << shapeCircle_.getArea() << std::endl;
  std::cout << shapeCircle_.getFrameRect().pos.x << " " << shapeCircle_.getFrameRect().pos.y << std::endl;
  shapeCircle_.move(3, 5);
  std::cout << shapeCircle_.getFrameRect().pos.x << " " << shapeCircle_.getFrameRect().pos.y << std::endl;
  shapeCircle_.move({14, 16});
  std::cout << shapeCircle_.getFrameRect().pos.x << " " << shapeCircle_.getFrameRect().pos.y << std::endl;

  printInfo(shapeRect_);
  printInfo(shapeCircle_);

  return 0;
}
