#include <iostream>
#include <memory>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace sergeev;
using std::cout;
using std::endl;
using std::cerr;

int main()
{
  try
  {
    CompositeShape c_shape;
  
    std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{{0.0,0.0},2.0,4.0});
    c_shape.add(rect);

    std::shared_ptr< Circle > circ = std::make_shared< Circle >(point_t{5.0,5.0}, 5.0);
    c_shape.add(circ);

    cout << "------------------------------------------------------" << endl;
    cout << "\t\tConstructed shape: " << endl;
    cout << "Area: " << c_shape.getArea() << endl;
    cout << "FrameRect: " << endl;
    cout << "x = " << c_shape.getFrameRect().pos.x << endl;
    cout << "y = " << c_shape.getFrameRect().pos.y << endl;
    cout << "width = " << c_shape.getFrameRect().width << endl;
    cout << "height = " << c_shape.getFrameRect().height << endl;
    cout << "------------------------------------------------------" << endl;
    c_shape.move(10.0,10.0);
    cout << "\t\tMoved shape(10.0,10.0): " << endl;
    cout << "Area: " << c_shape.getArea() << endl;
    cout << "FrameRect: " << endl;
    cout << "x = " << c_shape.getFrameRect().pos.x << endl;
    cout << "y = " << c_shape.getFrameRect().pos.y << endl;
    cout << "width = " << c_shape.getFrameRect().width << endl;
    cout << "height = " << c_shape.getFrameRect().height << endl;
    cout << "------------------------------------------------------" << endl;
    c_shape.scale(2.0);
    cout << "\t\tScaled shape(factor = 2.0): " << endl;
    cout << "Area: " << c_shape.getArea() << endl;
    cout << "FrameRect: " << endl;
    cout << "x = " << c_shape.getFrameRect().pos.x << endl;
    cout << "y = " << c_shape.getFrameRect().pos.y << endl;
    cout << "width = " << c_shape.getFrameRect().width << endl;
    cout << "height = " << c_shape.getFrameRect().height << endl;
    cout << "------------------------------------------------------" << endl;
    }
  catch(std::exception & ex)
  {
    cerr << ex.what() << endl;
    return 2;
  }
  return 0;
}
