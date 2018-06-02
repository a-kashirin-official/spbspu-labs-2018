#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "shape.hpp"

void PrintFrameRectInfo(const Shape & shapeX, const char * name)
{
  rectangle_t framerect = shapeX.getFrameRect();
  std::cout << "Shape:" << name << std::endl
  << "X:" << framerect.pos.x
  << "Y:" << framerect.pos.y
  << "Width:" << framerect.width
  << "Height:" << framerect.height << std::endl;
}

void PrintAreaInfo(const Shape & shape1, const char * name)
{
  std::cout << "Area" << name << " is " << shape1.getArea() << std::endl;
}

int main()
{
  try
  {
    point_t newpos{-1.0 , 1.0};

    Circle Circle1({4.0 , 4.0} , 6.0);
    PrintFrameRectInfo(Circle1," Circle ");
    PrintAreaInfo(Circle1," Circle");
    
    Rectangle Rectangle1({ {8.0 , 2.0} , 4.0 , 6.0});
    PrintFrameRectInfo(Rectangle1," Rectangle ");
    PrintAreaInfo(Rectangle1," Rectangle ");

    Rectangle1.move(5.0 , -6.0);
    PrintFrameRectInfo(Rectangle1," Rectangle ");
    Rectangle1.move(newpos);
    PrintFrameRectInfo(Rectangle1," Rectangle ");

  }
  catch(std::invalid_argument & errr)
  {
    std::cerr << errr.what() << std::endl;
    return(1);
  }
  return(0);
}
