#include <iostream>
#include <rectangle.hpp>
#include <circle.hpp>

using namespace vasilev;
void getLog(const Shape &testshape)\
{
  testshape.getInfo();
}
int main()
{
  Rectangle rect(40, 20, {100, 100});
  Circle circ(20, {100, 100});
  getLog(rect);
  getLog(circ);
  std::cout << std::endl <<"Moving rectangle for (5,10)" << std::endl;
  rect.move(5, 10);
  getLog(rect);
  std::cout << std::endl << "Moving circle to (0,0)" << std::endl;
  circ.move({0, 0});
  getLog(circ);
  std::cout << std::endl << "Scaling rectangle by 4" << std::endl;
  rect.scale(4);
  getLog(rect);
  std::cout << std::endl << "Scaling circle by 4" << std::endl;
  circ.scale(4);
  getLog(circ);
  return 0;
}
