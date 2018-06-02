#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

void showHowItWorks(zabrodina::Shape *ptr)
{
  ptr->printInf();
  ptr->move({5.0,2.0});
  std::cout << "Move to {2,5}: " << std::endl;
  ptr->printInf();
  ptr->move(5.0,2.0);
  std::cout << "Move on x=2,y=5: " << std::endl;
  ptr->printInf();
  ptr->scale(2.0);
  std::cout << "Scale by 2: " << std::endl;
  ptr->printInf();
  std::cout << std::endl;
}

int main()
{
  try
  {
    zabrodina::Rectangle rect({1.0,4.0},6.0,2.0);
    std::cout << "RECTANGLE:" << std::endl;
    showHowItWorks(&rect);
    zabrodina::Circle circl({1.0,7.0},-5.0);
    std::cout << "CIRCLE:" << std::endl;
    showHowItWorks(&circl);
    zabrodina::Triangle triangl({0.0,0.0}, {3.0,4.0}, {0.0,6.0});
    std::cout << "TRIANGLE:" << std::endl;
    showHowItWorks(&triangl);
  }
  catch(const std::invalid_argument &e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  return 0;
}
