#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "base-types.hpp"

using namespace std;

int main()
{
  Circle circle({1, 1}, 10);
  cout << "==> The circle has been created. Shape info:" << endl;
  cout << circle.getInfo() << endl;

  Rectangle rectangle({-4, -9}, 3, 2);
  cout << "==> The rectangle has been created. Shape info:" << endl;
  cout << rectangle.getInfo() << endl;

  point_t vertices[3] = {{1, 1}, {4, 1}, {1, 10}};
  Triangle triangle(vertices);
  cout << "==> The triangle has been created. Shape info:" << endl;
  cout << triangle.getInfo() << endl;

  Shape* shape;
  
  shape = &circle;
  shape->move({2, 3});
  cout << "==> The circle has been moved to the point. Shape info:" << endl;
  cout << shape->getInfo() << endl;
  
  shape = &rectangle;
  shape->move(10, 20);
  cout << "==> The rectangle has been moved with the shift. Shape info:" << endl;
  cout << shape->getInfo() << endl;
  
  shape = nullptr;
}
