#include <iostream>
#include <memory>
#include "../common/circle.hpp"
#include "../common/rectangle.hpp"
#include "../common/composite-shape.hpp"

using namespace std;
using namespace belonogova;

int main()
{
  try {
    shared_ptr <Shape> rect1 = make_shared<Rectangle>(Rectangle({9.0, 5.0, {-1.0, 7.0}}));
    shared_ptr <Shape> rect2 = make_shared<Rectangle>(Rectangle({24.2, 0.0, {3.0, -5.2}}));
    shared_ptr <Shape> circ1 = make_shared<Circle>(Circle(2.9, {13.0, 0.0}));
    CompositeShape comp(rect1);
    comp.addComponent(circ1);
    comp.addComponent(rect2);

    cout << "---Composite Shape---" << endl
         << "Area: " << comp.getArea() << endl
         << "Frame: center (" << comp.getFrameRect().pos.x << ", " << comp.getFrameRect().pos.y << ")" << endl
         << "width = " << comp.getFrameRect().width << ", height = " << comp.getFrameRect().height << endl;

    comp.move({6.0, 6.0});
    cout << "Moving to {6.0, 6.0} : " << endl
         << "new center (" << comp.getFrameRect().pos.x << ", " << comp.getFrameRect().pos.y << ")" << endl;

    comp.scale(0.5);
    cout << "Scaling with coef 0.5 : " << endl
         << "new area : " << comp.getArea() << endl;

    cout << "Removing shape no.1" << endl;
    comp.removeComponent(1);
    cout << "Composite shape area = " << comp.getArea() << endl;

  }
  catch (invalid_argument & error) {
    cerr << "Error : " << error.what() << endl;
    return 1;
  }
  catch (out_of_range & error) {
    cerr << "Error : " << error.what() << endl;
    return 1;
  }
  return 0;
}
