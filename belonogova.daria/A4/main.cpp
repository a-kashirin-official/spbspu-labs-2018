#include <iostream>
#include <memory>
#include "../common/circle.hpp"
#include "../common/rectangle.hpp"
#include "../common/composite-shape.hpp"

using namespace std;
using namespace belonogova;

int main ()
{
  try {
    shared_ptr <Shape> rect0 = make_shared<Rectangle>(Rectangle({2.0, 2.0, {-5.0, 4.0}}));
    shared_ptr <Shape> rect1 = make_shared<Rectangle>(Rectangle({4.0, 2.0, {-2.0, 4.0}}));
    shared_ptr <Shape> rect2 = make_shared<Rectangle>(Rectangle({6.0, 2.0, {-3.0, 2.0}}));
    shared_ptr <Shape> circ3 = make_shared<Circle>(Circle(2.0, {0.0, 6.0}));
    shared_ptr <Shape> rect4 = make_shared<Rectangle>(Rectangle({1.0, 1.0, {2.0, 1.0}}));
    shared_ptr <Shape> rect5 = make_shared<Rectangle>(Rectangle({1.0, 4.0, {1.5, 8.0}}));
    CompositeShape comp(rect0);
    comp.addComponent(rect1);
    comp.addComponent(rect2);
    comp.addComponent(circ3);
    comp.addComponent(rect4);
    comp.addComponent(rect5);

    cout << "frameRect of Composite shape : " << endl
         << "width = " << comp.getFrameRect().width << endl
         << "height = " << comp.getFrameRect().height << endl
         << "center (" << comp.getFrameRect().pos.x << ", " << comp.getFrameRect().pos.y <<")" << endl
         << "Area: " << comp.getArea() << endl << endl;
    comp.rotate(90);
    cout << "After rotating on 90 deg. :" << endl
        << "width = " << comp.getFrameRect().width << endl
        << "height = " << comp.getFrameRect().height << endl
        << "center (" << comp.getFrameRect().pos.x << ", " << comp.getFrameRect().pos.y <<")" << endl
        << "Area: " << comp.getArea() << endl << endl;

    Matrix matr = comp.formMatrix();
    cout << "Matrix of this Composite shape:" << endl
         << matr.getLayers() << " layers, " << matr.getMaxInLayer() << " maximum shapes in layer" << endl;
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
