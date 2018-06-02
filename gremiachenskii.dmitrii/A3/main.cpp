#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"
using namespace std;
using namespace gremiachenskii;

void print(const Shape & figure)
{
  rectangle_t rect = figure.getFrameRect();
  std::cout << "AREA: " << figure.getArea() << std::endl;
  std::cout << "COORDINATES: (" << rect.pos.x << ", " << rect.pos.y << ")" << std::endl;
  std::cout << "FRAME RECT: " << std::endl
            << "* Height: " << rect.height << std::endl
            << "* Width: " << rect.width << std::endl;
}

int main()
{
  try
  {
    cout << "=== RECTANGLE ===" << endl;
    Rectangle rect( {10.0, 10.0}, 30.0, 40.0 );
    print(rect);
    rect.move( 10.0, 150.0 );
    print(rect);
    rect.move( {0.0, 0.0} );
    print(rect);
    rect.scale(2.0);
    print(rect);

    cout << "=== CIRCLE ===" << endl;
    Circle circ( {15.0, 25.5}, 13.0 );
    print(circ);
    circ.move( 10.0, 150.0 );
    print(circ);
    circ.move( {0.0, 0.0} );
    print(circ);
    circ.scale(2.0);
    print(circ);

    cout << "=== COMPOSITE SHAPE ===" << endl;
    shared_ptr<Shape> rectPtr = make_shared<Rectangle>(Rectangle( {20.0, 30.0}, 50.0, 30.0 ));
    shared_ptr<Shape> circPtr = make_shared<Circle>(Circle({ 1.0, 1.0 }, 20.0));
    CompositeShape compShape(rectPtr);
    compShape.addElement(circPtr);
    cout << compShape.getSize() << " elements" << endl;
    print(compShape);
    compShape.removeElement(0);
    cout << compShape.getSize() << " elements" << endl;
    print(compShape);
  }
  catch(invalid_argument & except)
  {
    cerr << except.what() << endl;
  }
  catch(out_of_range & except)
  {
    cerr << except.what() << endl;
  }
}
