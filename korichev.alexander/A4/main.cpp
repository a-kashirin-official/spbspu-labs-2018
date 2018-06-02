#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

#include <iostream>
#include <memory>

using namespace korichev;

void test(Shape & testerx)
{
  std::cout << "Area is: " << testerx.getArea() << std::endl;
  std::cout << "Current coordinates: (" << testerx.getFrameRect().pos.x << ", " << testerx.getFrameRect().pos.y<<')'<<std::endl;
  testerx.move(6,3);
  std::cout << "Coordinates (moved 6 3): (" << testerx.getFrameRect().pos.x << ", " << testerx.getFrameRect().pos.y<<')'<<std::endl;
  testerx.move({3.5,2});
  std::cout << "Coordinates (moved to (3.5,2)): (" << testerx.getFrameRect().pos.x << ", " << testerx.getFrameRect().pos.y<<')'<<std::endl;
  testerx.scale(2.0);
  std::cout << "Scaled shape by 2, current area: " << testerx.getArea() << std::endl;
  std::cout << "FrameRect is: " <<std::endl;
  std::cout << '(' << testerx.getFrameRect().pos.x << ',' << testerx.getFrameRect().pos.y << ") " << std::endl;
  std::cout << testerx.getFrameRect().width << std::endl;
  std::cout << testerx.getFrameRect().height << std::endl;
  testerx.rotate(-45);
  std::cout << "Rotated by -45 degrees, area is: " << testerx.getArea() << std::endl;

  std::cout << "FrameRect is: " <<std::endl;
  std::cout << '(' << testerx.getFrameRect().pos.x << ',' << testerx.getFrameRect().pos.y << ") " << std::endl;
  std::cout << "width = " << testerx.getFrameRect().width << std::endl;
  std::cout << "height = " << testerx.getFrameRect().height << std::endl;
}

int main()
{
  Rectangle rect1_({-10,-10},1,1);
  Rectangle rectangle_({10,10},1,1);
  CompositeShape comp_;
  std::shared_ptr< korichev::Shape> temp = std::make_shared< korichev::Rectangle> (rectangle_);
  comp_.add(temp);
  temp = std::make_shared< korichev::Rectangle> (rect1_);
  comp_.add(temp);
  try
  {
    test(comp_);

    Matrix matrix = comp_.getMatrix();
    std::cout << "Matrix:" << '\n';
    for (size_t i = 0; i < matrix.getLayers(); i++) {
      for (size_t j = 0; j < matrix.getLayerSize(); j++) {
        std::cout << '(' << matrix[i][j]->getFrameRect().pos.x << ',' << matrix[i][j]->getFrameRect().pos.y << ") ";
      }
      std::cout<<std::endl;
    }

  } catch ( std::invalid_argument & problem)
  {
    std::cerr << problem.what() << std::endl;
    return 1;
  }
  return 0;
}
