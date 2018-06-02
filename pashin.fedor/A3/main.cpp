#include <iostream>

#include "composite-shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "base-types.hpp"

using namespace std;
using namespace pashin;

int main()
{
  CompositeShape composite_shape;
  cout << "==> The composite shape has been created" << endl << endl;

  Circle circle({1, 1}, 10);
  cout << "==> The circle has been created. Shape info:" << endl;
  cout << circle.getInfo() << endl;
  composite_shape.addShape(&circle);
  cout << "==> The circle has been added to the composite shape" << endl << endl;

  Rectangle rectangle({-4, -9}, 3, 2);
  cout << "==> The rectangle has been created. Shape info:" << endl;
  cout << rectangle.getInfo() << endl;
  composite_shape.addShape(&rectangle);
  cout << "==> The rectangle has been added to the composite shape" << endl << endl;

  composite_shape.move({2, 3});
  cout << "==> The composite shape has been moved to the point. Shape info:" << endl;
  cout << composite_shape.getInfo() << endl;
  
  composite_shape.scale(2);
  cout << "==> The composite shape has been scaled with the coefficient. Shape info:" << endl;
  cout << composite_shape.getInfo() << endl;
  
  composite_shape.removeShape(&circle);
  cout << "==> The circle has been removed from the composite shape. Shape info:" << endl << endl;
  cout << composite_shape.getInfo() << endl;
}
