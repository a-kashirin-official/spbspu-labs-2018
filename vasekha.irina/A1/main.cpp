#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"

void test(Shape & shape)
{
  std::cout << shape;
  std::cout << "Area=" << shape.getArea() << std::endl;
  rectangle_t frame = shape.getFrameRect();
  std::cout << "Frame: (" << frame.pos.x << "," << frame.pos.y << "), width=" << frame.width 
    << " height=" << frame.height << std::endl;
  shape.move({3.0,3.0});
  std::cout << "move to point" << std::endl << shape;
  shape.move(1.0,6.0);
  std::cout << "move dx, dy" << std::endl << shape << std::endl;
}

int main()
{
  try
  {
    Rectangle rect{{2.0,3.0},4.0,4.0};
    Circle cir{{1.0,1.0},1.0};
    Triangle tr{{-6.0,3.0},{-4.0,3.0},{-1.0,8.0}};
    test(rect);
    test(cir);
    test(tr);
  }
  catch(const std::invalid_argument & e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
};
