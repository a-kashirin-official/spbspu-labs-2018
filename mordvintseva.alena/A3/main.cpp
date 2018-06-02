#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace mordvintseva;
using std::cout;
using std::endl;
using std::cerr;

int main()
{
  try 
  {
    //Shapes for composite shape
    Rectangle rect({ 20.0, 40.0, { -5.0, 30.0 } });
    Circle circle(20.0, { 10.0, 13.4 });
    
    CompositeShape compositeShape(&rect);
    //cout << "Composite shape's size: " << compositeShape.getCount() << endl;
    //compositeShape.add(&circle);

    cout << "Area with rectangle: " << compositeShape.getArea() << endl;
    cout << "Frame rectangle: width = " << compositeShape.getFrameRect().width << ", height = " << compositeShape.getFrameRect().height << endl;
    cout << "         center: x = " << compositeShape.getFrameRect().pos.x << " y = " << compositeShape.getFrameRect().pos.y; 
    cout << endl;

    compositeShape.add(&circle);
    cout << "Area with rectangle and circle: " << compositeShape.getArea() << endl;
    cout << "Frame rectangle: width = " << compositeShape.getFrameRect().width << ", height = " << compositeShape.getFrameRect().height << endl;
    cout << "         center: x = " << compositeShape.getFrameRect().pos.x << " y = " << compositeShape.getFrameRect().pos.y; 
    cout << endl;
    cout << "Composite shape's size: " << compositeShape.getCount() << endl;
    cout << endl;

    compositeShape.scale(2.0);
    cout << "Area after scaling x2: " << compositeShape.getArea() << endl;
    cout << "Frame rectangle: width = " << compositeShape.getFrameRect().width << ", height = " << compositeShape.getFrameRect().height << endl;
    cout << "         center: x = " << compositeShape.getFrameRect().pos.x << " y = " << compositeShape.getFrameRect().pos.y; 
    cout << endl;

    cout << "Removing the first item of composite shape..." << endl;
    compositeShape.remove(0);
    
    cout << "Area with circle: " << compositeShape.getArea() << "; circle area: " << circle.getArea() << endl;
    cout << "Frame rectangle: width = " << compositeShape.getFrameRect().width << ", height = " << compositeShape.getFrameRect().height << endl;
    cout << "         center: x = " << compositeShape.getFrameRect().pos.x << " y = " << compositeShape.getFrameRect().pos.y; 
    cout << endl;

    cout << "Composite shape's size: " << compositeShape.getCount() << endl;
    cout << endl;
    return 0;
  } catch (std::invalid_argument& e) {
    cerr << e.what() << endl;
  } catch (std::out_of_range& e) {
    cerr << e.what() << endl;
  }
}
