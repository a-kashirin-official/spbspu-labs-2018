#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

void getLog(const Shape &testshape)
{
  testshape.getInfo();
}
int main()
{
  Rectangle rect(64, 32, {50, 50});
  Circle circ(15,  {100,100});
  getLog(rect);
  getLog(circ);
  std::cout << std::endl <<"Moving rectangle for (5,10)" << std::endl;
  rect.move(5, 10);
  getLog(rect);
  std::cout << std::endl << "Moving circle to (0,0)" << std::endl;
  circ.move({0, 0});
  getLog(circ);
  return 0;
}
