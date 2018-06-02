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

  Circle shape_1({-52, -91}, 10);
  cout << "==> Shape 1 has been created. Shape info:" << endl;
  cout << shape_1.getInfo() << endl;
  composite_shape.addShape(&shape_1);
  cout << "==> Shape 1 has been added to the composite shape" << endl << endl;

  Rectangle shape_2({-4, -9}, 3, 2);
  cout << "==> Shape 2 has been created. Shape info:" << endl;
  cout << shape_2.getInfo() << endl;
  composite_shape.addShape(&shape_2);
  cout << "==> Shape 2 has been added to the composite shape" << endl << endl;
  
  Rectangle shape_3({1, 1}, 10, 23);
  cout << "==> Shape 3 has been created. Shape info:" << endl;
  cout << shape_3.getInfo() << endl;
  composite_shape.addShape(&shape_3);
  cout << "==> Shape 3 has been added to the composite shape" << endl << endl;
  
  cout << "==> Composite shape info:" << endl;
  cout << composite_shape.getInfo() << endl;

  composite_shape.removeShape(&shape_1);
  cout << "==> Shape 1 has been removed from the composite shape. Shape info:" << endl << endl;
  cout << composite_shape.getInfo() << endl;
}
