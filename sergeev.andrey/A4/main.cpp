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

    std::shared_ptr< Rectangle > rect = std::make_shared< Rectangle >(rectangle_t{ {5.0, 5.0}, 10.0, 10.0 });
    c_shape.add(rect);

    std::shared_ptr< Circle > circle = std::make_shared< Circle >(point_t{0.0, 0.0}, 5.0);
    c_shape.add(circle);

    cout << "\tConstructed shape: " << endl;
    cout << "Area = " << c_shape.getArea() << endl;
    cout << "Frame rect:" << endl;
    cout << "x = " << c_shape.getFrameRect().pos.x << ", y = " << c_shape.getFrameRect().pos.y << endl;
    cout << "width = " << c_shape.getFrameRect().width << ", height = " << c_shape.getFrameRect().height << endl;
    cout << endl;

    cout << "\tAfter rotate(50)" << endl;
    c_shape.rotate(50.0);
    cout << "Area = " << c_shape.getArea() << endl;
    cout << "Frame rect:" << endl;
    cout << "x = " << c_shape.getFrameRect().pos.x << ", y = " << c_shape.getFrameRect().pos.y << endl;
    cout << "width = " << c_shape.getFrameRect().width << ", height = " << c_shape.getFrameRect().height << endl;
    cout << endl;

    Matrix mat = c_shape.devide();

    for(size_t i = 0; i < mat.getLayers(); ++i)
    {
      Matrix::layer_type layer = mat[i];
      cout << "\tLayer #" << i << endl;
      for(size_t j = 0; j < mat.getLayerSize(); ++j)
      {
        if(!layer[j])
        {
          break;
        }
        cout << "\tElement #" << j << endl;
        cout << "Area = " << layer[j]->getArea() << endl;
        cout << "Frame rect:" << endl;
        cout << "x = " << layer[j]->getFrameRect().pos.x << ", y = " << layer[j]->getFrameRect().pos.y << endl;
        cout << "width = " << layer[j]->getFrameRect().width << ", height = " << layer[j]->getFrameRect().height << endl;
        cout << endl;
      }
    }
  }
  catch(const std::exception & ex)
  {
    cerr << ex.what() << endl;
    return 1;
  }
  return 0;
}
