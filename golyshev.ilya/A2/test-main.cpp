#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include <boost/test/included/unit_test.hpp>


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
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, 2, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, 2, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(MOVE_BY_dx_OR_dy)
  {
    golyshev::Circle circle{10.0, {1, 1}};
    circle.move(2, 2);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, 20.0, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, 20.0, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, 3, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, 3, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(GET_AREA)
  {
    golyshev::Circle circle{10.0, {1, 1}};
    BOOST_CHECK_CLOSE(circle.getArea(), 314.15926535897933, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(SCALE)
  {
    golyshev::Circle circle{10.0, {1, 1}};
    circle.scale(2);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, 40, Accuracy);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, 40, Accuracy);
    BOOST_CHECK_CLOSE(circle.getArea(), 1256.6370614359173, Accuracy);
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
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, 3, Accuracy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, 3, Accuracy);
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
    BOOST_CHECK_CLOSE(rectangle.getArea(), 4, Accuracy);
    BOOST_CHECK_THROW(rectangle.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TRIANGLE_TESTS)
  const double Accuracy = 0.01;

  BOOST_AUTO_TEST_CASE(MOVE_TO_POINT)
  {
    golyshev::Triangle triangle({1.0, 1.0}, {2.0, 2.0}, {2.0, 0.0});
    triangle.move({2.0, 2.0});
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, 0.99999999999999978, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, 2, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, 1.833333333333333, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, 2, Accuracy);
  }

  BOOST_AUTO_TEST_CASE(MOVE_BY_dx_OR_dy)
  {
    golyshev::Triangle triangle({1.0, 1.0}, {2.0, 2.0}, {2.0, 0.0});
    triangle.move(2.0, 2.0);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, 1, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, 2, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, 3.5, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, 3, Accuracy);
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
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, 1.9999999999999998, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, 4, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, 1.333333333333333, Accuracy);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, 1, Accuracy);
    BOOST_CHECK_THROW(triangle.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
