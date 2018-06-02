#include <iostream>
#include "../common/circle.hpp"
#include "../common/rectangle.hpp"
#include "../common/triangle.hpp"
#include "../common/base-types.hpp"

using namespace isaev;
using namespace std;

int main()
{
  point_t p = {0, 0};
  Rectangle rect(p, 5, 10);
  Shape *ptr = &rect;
  ptr->printShapeInfo();
  std::cout << "Area is = " << ptr->getArea() << "\n";
  ptr->scale(3);
  std::cout << "After scaling to 3: " << "\n";
  ptr->printShapeInfo();

  Circle cir(p ,3);
  ptr = &cir;
  ptr->printShapeInfo();
  std::cout << "Area is = " << ptr->getArea() << "\n";
  ptr->scale(5);
  std::cout << "After scaling to 5 " << "\n";
  ptr->printShapeInfo();

  point_t p1 = {0, 0};
  point_t p2 = {10, 10};
  point_t p3 = {20, 0};
  Triangle tri ( p1, p2, p3);
  ptr = &tri;
  ptr->printShapeInfo();
  std::cout << "Area is = " << ptr->getArea() << "\n";
  ptr->scale(10);
  std::cout << "After scaling to 10 : " << "\n";
  ptr->printShapeInfo();

  return 0;
}
