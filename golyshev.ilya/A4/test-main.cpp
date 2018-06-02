#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <cmath>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"
#include "matrix.hpp"
#include "polygon.hpp"
#include <boost/test/included/unit_test.hpp>

using namespace golyshev;
//Testing class Circle
BOOST_AUTO_TEST_SUITE(CIRCLE_TESTS)
  const double Accuracy = 0.01;

  BOOST_AUTO_TEST_CASE(CONSTRUCTOR)
  {
    BOOST_CHECK_THROW(golyshev::Circle circle(-10.0, {1, 1}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MOVE_TO_POINT)
  {
    golyshev::Circle circle{10.0, {1, 1}};
    circle.move({2, 2});
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, 20.0, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, 20.0, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, 2.0, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, 2.0, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(MOVE_BY_dx_OR_dy)
  {
    golyshev::Circle circle{10.0, {1, 1}};
    circle.move(2, 2);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, 20.0, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, 20.0, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, 3.0, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, 3.0, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(GET_AREA)
  {
    golyshev::Circle circle{10.0, {1, 1}};
    BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 10.0 * 10.0, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(SCALE)
  {
    golyshev::Circle circle{10.0, {1, 1}};
    circle.scale(2);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, 40, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, 40, Accuracy);
    BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 20.0 * 20.0, Accuracy);
    BOOST_CHECK_THROW(circle.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()


//Testing class Rectangle
BOOST_AUTO_TEST_SUITE(RECTANGLE_TESTS)
  const double Accuracy = 0.01;

  BOOST_AUTO_TEST_CASE(CONSTRUCTOR)
  {
    BOOST_CHECK_THROW(golyshev::Rectangle rectangle(-1.0, 1.0, {1, 1}), std::invalid_argument);
    BOOST_CHECK_THROW(golyshev::Rectangle rectangle(1.0, -1.0, {1, 1}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MOVE_TO_POINT)
  {
    golyshev::Rectangle rectangle(1.0, 1.0, {1, 1});
    golyshev::Rectangle rectangle1 = rectangle;
    rectangle.move({2, 2});
    rectangle1.move({2, 2});
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, rectangle1.getFrameRect().width, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, rectangle1.getFrameRect().height, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, rectangle1.getFrameRect().pos.x, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, rectangle1.getFrameRect().pos.y, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(MOVE_BY_dx_OR_dy)
  {
    golyshev::Rectangle rectangle(1.0, 1.0, {1, 1});
    rectangle.move(2, 2);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 1, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 1, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, 3.0, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, 3.0, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(GET_AREA)
  {
    golyshev::Rectangle rectangle(1.0, 1.0, {1, 1});
    BOOST_CHECK_CLOSE(rectangle.getArea(), 1, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(SCALE)
  {
    golyshev::Rectangle rectangle(1.0, 1.0, {1, 1});
    rectangle.scale(2);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 2, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 2, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getArea(), rectangle.getFrameRect().width * rectangle.getFrameRect().height, Accuracy);
    BOOST_CHECK_THROW(rectangle.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

//Testing class Triangle
BOOST_AUTO_TEST_SUITE(TRIANGLE_TESTS)
  const double Accuracy = 0.01;

  BOOST_AUTO_TEST_CASE(MOVE_TO_POINT)
  {
    golyshev::Triangle triangle({0.0, 0.0}, {2.0, 2.0}, {4.0, 0.0});
    triangle.move({2.0, 2.0});
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, 4.0, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, 2, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, 2.0, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, 2.3333333, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(MOVE_BY_dx_OR_dy)
  {
    golyshev::Triangle triangle({1.0, 1.0}, {2.0, 2.0}, {2.0, 0.0});
    triangle.move(2.0, 2.0);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, 1, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, 2, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, 3.5, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, 3.0, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(GET_AREA)
  {
    golyshev::Triangle triangle({1.0, 1.0}, {2.0, 2.0}, {2.0, 0.0});
    BOOST_CHECK_CLOSE(triangle.getArea(), 1, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(SCALE)
  {
    golyshev::Triangle triangle({1.0, 1.0}, {2.0, 2.0}, {2.0, 0.0});
    triangle.scale(2.0);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, 2, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, 4, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, 1.3333333, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, 1.0, Accuracy);
    BOOST_CHECK_THROW(triangle.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

//Testing class CompositeShape
class BOOST_CHECK_EQUAL;
BOOST_AUTO_TEST_SUITE(COMPOSITE_SHAPE_TESTS)
  const double Accuracy = 0.01;

  BOOST_AUTO_TEST_CASE(MOVE_TO_POINT)
  {
    golyshev::Rectangle rect1(1, 1, {1.5, 1.5});
    golyshev::Rectangle rect2(1, 1, {2.5, 2.5});
    golyshev::Rectangle rect3(1, 1, {3.5, 3.5});
    std::shared_ptr<golyshev::Shape> rectPtr1 = std::make_shared<golyshev::Rectangle>(rect1);
    std::shared_ptr<golyshev::Shape> rectPtr2 = std::make_shared<golyshev::Rectangle>(rect2);
    std::shared_ptr<golyshev::Shape> rectPtr3 = std::make_shared<golyshev::Rectangle>(rect3);
    golyshev::CompositeShape testCompositeShape(rectPtr1);
    testCompositeShape.add(rectPtr2);
    testCompositeShape.add(rectPtr3);
    testCompositeShape.move({15, 10});
    BOOST_CHECK_CLOSE(testCompositeShape.getFrameRect().pos.x, 11.625, Accuracy);
    BOOST_CHECK_CLOSE(testCompositeShape.getFrameRect().pos.y, 7.875, Accuracy);
    BOOST_CHECK_EQUAL(testCompositeShape.getArea(), 3);
  }


  BOOST_AUTO_TEST_CASE(MOVE_BY_DX_DY)
  {
    golyshev::Rectangle rect1(1, 1, {1.5, 1.5});
    golyshev::Rectangle rect2(1, 1, {2.5, 2.5});
    golyshev::Rectangle rect3(1, 1, {3.5, 3.5});
    std::shared_ptr<golyshev::Shape> rectPtr1 = std::make_shared<golyshev::Rectangle>(rect1);
    std::shared_ptr<golyshev::Shape> rectPtr2 = std::make_shared<golyshev::Rectangle>(rect2);
    std::shared_ptr<golyshev::Shape> rectPtr3 = std::make_shared<golyshev::Rectangle>(rect3);
    golyshev::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.add(rectPtr2);
    testcompositeShape.add(rectPtr3);
    testcompositeShape.move(-1, 1);
    BOOST_CHECK_CLOSE(testcompositeShape.getFrameRect().pos.x, 1.5, Accuracy);
    BOOST_CHECK_CLOSE(testcompositeShape.getFrameRect().pos.y, 3.5, Accuracy);
    BOOST_CHECK_EQUAL(testcompositeShape.getArea(), 3);
  }

  BOOST_AUTO_TEST_CASE(AREA)
  {
    golyshev::Rectangle rect1(1, 1, {1.5, 1.5});
    golyshev::Rectangle rect2(1, 1, {2.5, 2.5});
    golyshev::Rectangle rect3(1, 1, {3.5, 3.5});
    std::shared_ptr<golyshev::Shape> rectPtr1 = std::make_shared<golyshev::Rectangle>(rect1);
    std::shared_ptr<golyshev::Shape> rectPtr2 = std::make_shared<golyshev::Rectangle>(rect2);
    std::shared_ptr<golyshev::Shape> rectPtr3 = std::make_shared<golyshev::Rectangle>(rect3);
    golyshev::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.add(rectPtr2);
    testcompositeShape.add(rectPtr3);
    BOOST_REQUIRE_EQUAL(testcompositeShape.getArea(), 3);
  }

  BOOST_AUTO_TEST_CASE(FRAME_RECT)
  {
    golyshev::Rectangle rect1(1, 1, {1.5, 1.5});
    golyshev::Rectangle rect2(1, 1, {2.5, 2.5});
    golyshev::Rectangle rect3(1, 1, {3.5, 3.5});
    std::shared_ptr<golyshev::Shape> rectPtr1 = std::make_shared<golyshev::Rectangle>(rect1);
    std::shared_ptr<golyshev::Shape> rectPtr2 = std::make_shared<golyshev::Rectangle>(rect2);
    std::shared_ptr<golyshev::Shape> rectPtr3 = std::make_shared<golyshev::Rectangle>(rect3);
    golyshev::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.add(rectPtr2);
    testcompositeShape.add(rectPtr3);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().pos.x, 2.5, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().pos.y, 2.5, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().width, 3, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().height, 3, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(SCALE)
  {
    golyshev::Rectangle rect1(1, 1, {1.5, 1.5});
    golyshev::Rectangle rect2(1, 1, {2.5, 2.5});
    golyshev::Rectangle rect3(1, 1, {3.5, 3.5});
    std::shared_ptr<golyshev::Shape> rectPtr1 = std::make_shared<golyshev::Rectangle>(rect1);
    std::shared_ptr<golyshev::Shape> rectPtr2 = std::make_shared<golyshev::Rectangle>(rect2);
    std::shared_ptr<golyshev::Shape> rectPtr3 = std::make_shared<golyshev::Rectangle>(rect3);
    golyshev::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.add(rectPtr2);
    testcompositeShape.add(rectPtr3);
    testcompositeShape.scale(4);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getArea(), 48, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().pos.x, 2.5, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().pos.y, 2.5, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().width, 8, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().height, 8, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(REMOVE)
  {
    golyshev::Rectangle rect1(1, 1, {1.5, 1.5});
    golyshev::Rectangle rect2(1, 1, {2.5, 2.5});
    golyshev::Rectangle rect3(1, 1, {3.5, 3.5});
    std::shared_ptr<golyshev::Shape> rectPtr1 = std::make_shared<golyshev::Rectangle>(rect1);
    std::shared_ptr<golyshev::Shape> rectPtr2 = std::make_shared<golyshev::Rectangle>(rect2);
    std::shared_ptr<golyshev::Shape> rectPtr3 = std::make_shared<golyshev::Rectangle>(rect3);
    golyshev::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.add(rectPtr2);
    testcompositeShape.add(rectPtr3);
    testcompositeShape.remove(0);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().pos.x, 3, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().pos.y, 3, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().width, 2, Accuracy);
    BOOST_CHECK_CLOSE_FRACTION(testcompositeShape.getFrameRect().height, 2, Accuracy);
  }


  BOOST_AUTO_TEST_CASE(INVALID_ARGUMENT)
  {
    golyshev::Circle circ(10, {0, 0});
    std::shared_ptr<golyshev::Shape> circPtr = std::make_shared<golyshev::Circle>(circ);
    golyshev::CompositeShape testcompositeShape(circPtr);
    BOOST_CHECK_THROW(testcompositeShape.scale(-1), std::invalid_argument);
    BOOST_CHECK_THROW(testcompositeShape.remove(2), std::out_of_range);
    BOOST_CHECK_THROW(testcompositeShape[2], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(OPERATOR_COPY)
  {
    golyshev::Rectangle rect1(1, 1, {1.5, 1.5});
    golyshev::Rectangle rect2(1, 1, {2.5, 2.5});
    golyshev::Rectangle rect3(1, 1, {3.5, 3.5});

    std::shared_ptr<golyshev::Shape> rectPtr1 = std::make_shared<golyshev::Rectangle>(rect1);
    std::shared_ptr<golyshev::Shape> rectPtr2 = std::make_shared<golyshev::Rectangle>(rect2);
    std::shared_ptr<golyshev::Shape> rectPtr3 = std::make_shared<golyshev::Rectangle>(rect3);

    golyshev::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.add(rectPtr2);
    testcompositeShape.add(rectPtr3);

    golyshev::Rectangle rect4(2, 2, {1.5, 1.5});
    golyshev::Rectangle rect5(2, 2, {2.5, 2.5});
    golyshev::Rectangle rect6(2, 2, {3.5, 3.5});

    std::shared_ptr<golyshev::Shape> rectPtr4 = std::make_shared<golyshev::Rectangle>(rect4);
    std::shared_ptr<golyshev::Shape> rectPtr5 = std::make_shared<golyshev::Rectangle>(rect5);
    std::shared_ptr<golyshev::Shape> rectPtr6 = std::make_shared<golyshev::Rectangle>(rect6);

    golyshev::CompositeShape testcompositeShape1(rectPtr4);
    testcompositeShape1.add(rectPtr5);
    testcompositeShape1.add(rectPtr6);

    testcompositeShape1 = testcompositeShape;

    for (size_t i = 0; i < testcompositeShape.size(); ++i) {
      golyshev::rectangle_t rectangle = testcompositeShape[i]->getFrameRect();
      golyshev::rectangle_t rectangle1 = testcompositeShape1[i]->getFrameRect();
      BOOST_CHECK_EQUAL(rectangle.height, rectangle1.height);
      BOOST_CHECK_EQUAL(rectangle.width, rectangle1.width);
      BOOST_CHECK_EQUAL(rectangle.pos.x, rectangle1.pos.x);
      BOOST_CHECK_EQUAL(rectangle.pos.y, rectangle1.pos.y);
    }
  }

  BOOST_AUTO_TEST_CASE(OPERATOR_MOVE)
  {
    golyshev::Rectangle rect1(1, 1, {1.5, 1.5});
    golyshev::Rectangle rect2(1, 1, {2.5, 2.5});
    golyshev::Rectangle rect3(1, 1, {3.5, 3.5});

    std::shared_ptr<golyshev::Shape> rectPtr1 = std::make_shared<golyshev::Rectangle>(rect1);
    std::shared_ptr<golyshev::Shape> rectPtr2 = std::make_shared<golyshev::Rectangle>(rect2);
    std::shared_ptr<golyshev::Shape> rectPtr3 = std::make_shared<golyshev::Rectangle>(rect3);

    golyshev::CompositeShape testcompositeShape(rectPtr1);
    testcompositeShape.add(rectPtr2);
    testcompositeShape.add(rectPtr3);

    golyshev::CompositeShape testcompositeShape1(testcompositeShape);
    golyshev::CompositeShape testcompositeShape2 = std::move(testcompositeShape);

    for (size_t i = 0; i < testcompositeShape.size(); ++i) {
      golyshev::rectangle_t rectangle = testcompositeShape1[i]->getFrameRect();
      golyshev::rectangle_t rectangle1 = testcompositeShape2[i]->getFrameRect();
      BOOST_CHECK_EQUAL(rectangle.height, rectangle1.height);
      BOOST_CHECK_EQUAL(rectangle.width, rectangle1.width);
      BOOST_CHECK_EQUAL(rectangle.pos.x, rectangle1.pos.x);
      BOOST_CHECK_EQUAL(rectangle.pos.y, rectangle1.pos.y);
    }
  }

BOOST_AUTO_TEST_SUITE_END()

//Testing class Matrix
class BOOST_CHECK_EQUAL;
BOOST_AUTO_TEST_SUITE(TEST_MATRIX)

  BOOST_AUTO_TEST_CASE(MATRIX_LAYERS)
  {
    golyshev::Rectangle rect1(4, 2, {0, 0});
    golyshev::Rectangle rect2(2, 4, {2, 0});
    golyshev::Rectangle rect3(2, 2, {-2, 3});

    std::shared_ptr<Shape> rect1s = std::make_shared<golyshev::Rectangle>(rect1);
    std::shared_ptr<Shape> rect2s = std::make_shared<golyshev::Rectangle>(rect2);
    std::shared_ptr<Shape> rect3s = std::make_shared<golyshev::Rectangle>(rect3);

    Matrix matrix(rect1s);
    matrix.add(rect2s);
    matrix.add(rect3s);

    BOOST_CHECK_EQUAL(matrix.getNumLayers() == 2, true);
  }

  BOOST_AUTO_TEST_CASE(GET_SHAPE)
  {
    golyshev::Rectangle rect1(4, 2, {0, 0});
    golyshev::Rectangle rect2(2, 4, {2, 0});
    golyshev::Rectangle rect3(2, 2, {-2, 3});

    std::shared_ptr<Shape> rect1s = std::make_shared<golyshev::Rectangle>(rect1);
    std::shared_ptr<Shape> rect2s = std::make_shared<golyshev::Rectangle>(rect2);
    std::shared_ptr<Shape> rect3s = std::make_shared<golyshev::Rectangle>(rect3);

    Matrix matrix(rect1s);
    matrix.add(rect2s);
    matrix.add(rect3s);

    BOOST_CHECK_EQUAL(matrix.getShape({0, 0}), rect1s);
    BOOST_CHECK_EQUAL(matrix.getShape({0, 1}), rect3s);
    BOOST_CHECK_EQUAL(matrix.getShape({1, 0}), rect2s);
  }

  BOOST_AUTO_TEST_CASE(ADD_FROM_COMPOSITE_SHAPE)
  {
    golyshev::Rectangle rect1(4, 2, {0, 0});
    golyshev::Rectangle rect2(2, 4, {2, 0});
    golyshev::Rectangle rect3(2, 2, {-2, 3});

    std::shared_ptr<Shape> rect1s = std::make_shared<golyshev::Rectangle>(rect1);
    std::shared_ptr<Shape> rect2s = std::make_shared<golyshev::Rectangle>(rect2);
    std::shared_ptr<Shape> rect3s = std::make_shared<golyshev::Rectangle>(rect3);

    CompositeShape cShape(rect1s);
    cShape.add(rect2s);
    cShape.add(rect3s);

    size_t sizes = cShape.size();
    std::shared_ptr<golyshev::CompositeShape> c_shape_ptr = std::make_shared<golyshev::CompositeShape>(cShape);
    Matrix matrix(rect1s);
    matrix.addFromCompositeShape(c_shape_ptr, sizes);

    BOOST_CHECK_EQUAL(matrix.getNumLayers() == 3, true);
  }

  BOOST_AUTO_TEST_CASE(GET_NUM_LAYERS)
  {
    golyshev::Rectangle rect1(4, 2, {0, 0});
    golyshev::Rectangle rect2(2, 4, {2, 0});
    golyshev::Rectangle rect3(2, 2, {-2, 3});

    std::shared_ptr<Shape> rect1s = std::make_shared<golyshev::Rectangle>(rect1);
    std::shared_ptr<Shape> rect2s = std::make_shared<golyshev::Rectangle>(rect2);
    std::shared_ptr<Shape> rect3s = std::make_shared<golyshev::Rectangle>(rect3);

    Matrix matrix(rect1s);
    matrix.add(rect2s);
    matrix.add(rect3s);

    matrix.getNumLayers();
    BOOST_CHECK_EQUAL(matrix.getNumLayers(), 2);
  }

  BOOST_AUTO_TEST_CASE(COPY_OPERATOR)
  {
    golyshev::Rectangle rect1(4, 2, {0, 0});
    golyshev::Rectangle rect2(2, 4, {2, 0});
    golyshev::Rectangle rect3(2, 2, {-2, 3});

    std::shared_ptr<Shape> rect1s = std::make_shared<golyshev::Rectangle>(rect1);
    std::shared_ptr<Shape> rect2s = std::make_shared<golyshev::Rectangle>(rect2);
    std::shared_ptr<Shape> rect3s = std::make_shared<golyshev::Rectangle>(rect3);

    CompositeShape cShape(rect1s);
    cShape.add(rect2s);
    cShape.add(rect3s);

    size_t sizes = cShape.size();
    std::shared_ptr<golyshev::CompositeShape> c_shape_ptr = std::make_shared<golyshev::CompositeShape>(cShape);
    Matrix matrix(rect1s);
    matrix.addFromCompositeShape(c_shape_ptr, sizes);

    Matrix matrix1(rect1s);
    matrix1 = matrix;

    std::size_t q1 = 0;
    std::size_t q2 = 1;
    std::size_t q3 = 2;
    BOOST_CHECK_EQUAL(matrix1.getShape(std::make_pair(q1, q1)), rect1s);
    BOOST_CHECK_EQUAL(matrix1.getShape(std::make_pair(q3, q1)), rect2s);
    BOOST_CHECK_EQUAL(matrix1.getShape(std::make_pair(q1, q2)), rect3s);
  }

  BOOST_AUTO_TEST_CASE(MOVE_OPERATOR)
  {
    golyshev::Rectangle rect1(4, 2, {0, 0});
    golyshev::Rectangle rect2(2, 4, {2, 0});
    golyshev::Rectangle rect3(2, 2, {-2, 3});

    std::shared_ptr<Shape> rect1s = std::make_shared<golyshev::Rectangle>(rect1);
    std::shared_ptr<Shape> rect2s = std::make_shared<golyshev::Rectangle>(rect2);
    std::shared_ptr<Shape> rect3s = std::make_shared<golyshev::Rectangle>(rect3);

    CompositeShape cShape(rect1s);
    cShape.add(rect2s);
    cShape.add(rect3s);

    size_t sizes = cShape.size();
    std::shared_ptr<golyshev::CompositeShape> c_shape_ptr = std::make_shared<golyshev::CompositeShape>(cShape);
    Matrix matrix(rect1s);
    matrix.addFromCompositeShape(c_shape_ptr, sizes);

    Matrix matrix1(rect1s);
    matrix1 = std::move(matrix);

    std::size_t q1 = 0;
    std::size_t q2 = 1;
    std::size_t q3 = 2;
    BOOST_CHECK_EQUAL(matrix1.getShape(std::make_pair(q1, q1)), rect1s);
    BOOST_CHECK_EQUAL(matrix1.getShape(std::make_pair(q3, q1)), rect2s);
    BOOST_CHECK_EQUAL(matrix1.getShape(std::make_pair(q1, q2)), rect3s);
  }

BOOST_AUTO_TEST_SUITE_END()

//Testing class Polygon
BOOST_AUTO_TEST_SUITE(TEST_POLYGON)
  const double EPS = 0.1;

  BOOST_AUTO_TEST_CASE(CONVEX)
  {
    BOOST_CHECK_THROW(golyshev::Polygon pol({{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}), std::invalid_argument);
  }


  BOOST_AUTO_TEST_CASE(GET_AREA)
  {
    golyshev::Polygon pol({{1, 1}, {3, 1}, {3, 3}, {1, 3}});
    golyshev::Polygon pol1 = pol;
    BOOST_CHECK_CLOSE(pol.getArea(), pol1.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(SCALE)
  {
    golyshev::Polygon pol({{1, 1}, {3, 1}, {3, 3}, {1, 3}});
    pol.scale(3);
    golyshev::Polygon pol1 = pol;
    BOOST_CHECK_CLOSE(pol.getArea(), pol1.getArea(), EPS);
  }

  BOOST_AUTO_TEST_CASE(MOVE_BY_DX_DY)
  {
    golyshev::Polygon pol({{1, 1}, {3, 1}, {3, 3}, {1, 3}});
    pol.move(3, 0);
    golyshev::Polygon pol1 = pol;
    BOOST_CHECK_CLOSE(pol.getCentre().x, pol1.getCentre().x, EPS);
    BOOST_CHECK_CLOSE(pol.getCentre().y, pol1.getCentre().y, EPS);
  }

  BOOST_AUTO_TEST_CASE(MOVE_TO_POINT)
  {
    golyshev::Polygon pol({{1, 1}, {3, 1}, {3, 3}, {1, 3}});
    golyshev::Polygon pol1 = pol;
    pol.move({5, 2});
    pol1.move({5, 2});
    BOOST_CHECK_CLOSE(pol.getCentre().x, pol1.getCentre().x, EPS);
    BOOST_CHECK_CLOSE(pol.getCentre().y, pol1.getCentre().y, EPS);
  }

  BOOST_AUTO_TEST_CASE(GET_FARME_RECT)
  {
    golyshev::Polygon pol({{1, 1}, {3, 1}, {3, 3}, {1, 3}});
    golyshev::Polygon pol1 = pol;
    BOOST_CHECK_CLOSE(pol.getFrameRect().width, pol1.getFrameRect().width, EPS);
    BOOST_CHECK_CLOSE(pol.getFrameRect().height, pol1.getFrameRect().height, EPS);
  }

BOOST_AUTO_TEST_SUITE_END()

