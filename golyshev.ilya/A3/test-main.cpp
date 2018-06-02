#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <cmath>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"
#include <boost/test/included/unit_test.hpp>

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

    golyshev::Rectangle rect4(2, 1, {1.5, 1.5});
    golyshev::Rectangle rect5(2, 1, {2.5, 2.5});
    golyshev::Rectangle rect6(2, 1, {3.5, 3.5});

    std::shared_ptr<golyshev::Shape> rectPtr4 = std::make_shared<golyshev::Rectangle>(rect1);
    std::shared_ptr<golyshev::Shape> rectPtr5 = std::make_shared<golyshev::Rectangle>(rect5);
    std::shared_ptr<golyshev::Shape> rectPtr6 = std::make_shared<golyshev::Rectangle>(rect6);

    golyshev::CompositeShape testcompositeShape1(rectPtr4);
    testcompositeShape.add(rectPtr5);
    testcompositeShape.add(rectPtr6);

    testcompositeShape1 = std::move(testcompositeShape);

    for (size_t i = 0; i < testcompositeShape.size(); ++i) {
      golyshev::rectangle_t rectangle = testcompositeShape[i]->getFrameRect();
      golyshev::rectangle_t rectangle1 = testcompositeShape1[i]->getFrameRect();
      BOOST_CHECK_EQUAL(rectangle.height, rectangle1.height);
      BOOST_CHECK_EQUAL(rectangle.width, rectangle1.width);
      BOOST_CHECK_EQUAL(rectangle.pos.x, rectangle1.pos.x);
      BOOST_CHECK_EQUAL(rectangle.pos.y, rectangle1.pos.y);
    }
  }

BOOST_AUTO_TEST_SUITE_END()
