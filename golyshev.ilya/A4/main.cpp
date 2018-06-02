#include <iostream>
#include <string>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include "polygon.hpp"

using namespace golyshev;

int main()
{
  try {

    Rectangle rectangle(1.0, 1.0, {-1.0, -1.0});
    Circle circle(1.0, {3.0, 3.0});
    Triangle triangle({0.0, 0.0}, {2.0, 2.0}, {4.0, 0.0});
    point_t t1 = {0, 0};
    point_t t2 = {0, 2};
    point_t t3 = {-1, 3};
    point_t t4 = {-2, 4};
    point_t t5 = {-3, 0};
    std::initializer_list<point_t> p = {t1, t2, t3, t4, t5};
    Polygon polygon(p);

    std::shared_ptr<Shape> circle_ptr = std::make_shared<Circle>(circle);
    std::shared_ptr<Shape> rectangle_ptr = std::make_shared<Rectangle>(rectangle);
    std::shared_ptr<Shape> triangle_ptr = std::make_shared<Triangle>(triangle);
    std::shared_ptr<Shape> polygon_ptr = std::make_shared<Polygon>(polygon);

    CompositeShape c_shape(circle_ptr);
    c_shape.add(rectangle_ptr);
    c_shape.add(triangle_ptr);
    size_t sizes = c_shape.size();
    std::shared_ptr<golyshev::CompositeShape> c_shape_ptr = std::make_shared<golyshev::CompositeShape>(c_shape);

    Matrix ShapeMat(circle_ptr);
    ShapeMat.add(rectangle_ptr);
    ShapeMat.add(triangle_ptr);
    ShapeMat.add(polygon_ptr);
    ShapeMat.addFromCompositeShape(c_shape_ptr, sizes);

    ShapeMat.OutInf(ShapeMat);
  }
  catch (std::exception &error) {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  return 0;
}
