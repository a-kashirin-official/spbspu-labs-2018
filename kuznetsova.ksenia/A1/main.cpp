
#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "shape.hpp"


void PrintArea(const Shape &shape1)
{
  std::cout << " Area " << shape1.getArea() << std::endl;
}

void PrintFrameRect(const Shape &shape1)
{
  rectangle_t framerect = shape1.getFrameRect();
  std::cout << "FrameRect " << std::endl
    << " centre.x " << framerect.pos.x
    << " centre.y " << framerect.pos.y
    << " width " << framerect.width
    << " height" << framerect.height << std::endl;
}

int main()
{
  point_t centre{ 1, 3 };
  point_t newcentre{ -1, -1 };

  Circle Circle1(centre, 3.4);
  PrintArea(Circle1);
  Circle1.move(newcentre);
  PrintFrameRect(Circle1);
  Circle1.move(-5, 3);
  PrintFrameRect(Circle1);

  std::cout << std::endl;

  Rectangle Rectangle1(centre, 5, 11);
  PrintArea(Rectangle1);
  Rectangle1.move(newcentre);
  PrintFrameRect(Rectangle1);
  Rectangle1.move(-10, 1);
  PrintFrameRect(Rectangle1);
  return 0;

}


