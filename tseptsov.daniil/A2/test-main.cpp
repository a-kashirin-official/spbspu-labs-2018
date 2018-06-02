#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "boost/test/included/unit_test.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"

using namespace tseptsov;

const double EPS = 0.00001;

BOOST_AUTO_TEST_SUITE(RectangleTests)

  BOOST_AUTO_TEST_CASE(Constructor)
  {
    BOOST_CHECK_THROW(tseptsov::Rectangle rectangle(-5, 7.5, {1, 2}), std::invalid_argument);
    BOOST_CHECK_THROW(tseptsov::Rectangle rectangle(5, -7.5, {1, 2}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Move_byAxes)
  {
    tseptsov::Rectangle rectangle(5, 7.5, {1, 2});
    rectangle.move(4, 5);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 5, EPS);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 7.5, EPS);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, 5, EPS);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, 7, EPS);
    BOOST_CHECK_CLOSE(rectangle.getArea(), 37.5, EPS);

  }

  BOOST_AUTO_TEST_CASE(Move_topoint)
  {
    tseptsov::Rectangle rectangle(5, 7.5, {1, 2});
    rectangle.move({4, 5});
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 5, EPS);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 7.5, EPS);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, 4, EPS);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, 5, EPS);
    BOOST_CHECK_CLOSE(rectangle.getArea(), 37.5, EPS);

  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    tseptsov::Rectangle rectangle(5, 7.5, {1, 2});
    BOOST_CHECK_CLOSE(rectangle.getArea(), 37.5, EPS);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    tseptsov::Rectangle rectangle(5, 7.5, {1, 2});
    rectangle.scale(1.5);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 7.5, EPS);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 11.25, EPS);
    BOOST_CHECK_CLOSE(rectangle.getArea(), 84.375, EPS);
    BOOST_CHECK_THROW(rectangle.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTests)

  BOOST_AUTO_TEST_CASE(Constructor)
  {
    BOOST_CHECK_THROW(Circle circle(-3.3, {1, 2}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Move_ToPoint)
  {
    Circle circle{3.0, {1, 2}};
    circle.move(4, 5);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height / 2, 3.0, EPS);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, 5, EPS);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, 7, EPS);
    BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 9.0, EPS);

  }

  BOOST_AUTO_TEST_CASE(Move_Delta)
  {
    Circle circle{3.0, {1, 2}};
    circle.move({4, 5});
    BOOST_CHECK_CLOSE(circle.getFrameRect().height / 2, 3.0, EPS);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, 4, EPS);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, 5, EPS);
    BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 9.0, EPS);

  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    Circle circle{3, {1, 2}};
    BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 9, EPS);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    Circle circle{3, {1, 2}};
    circle.scale(2);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height / 2, 6, EPS);
    BOOST_CHECK_CLOSE(circle.getArea(), M_PI * 36, EPS);
    BOOST_CHECK_THROW(circle.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TriangleTests)

  BOOST_AUTO_TEST_CASE(Move_ToPoint)
  {
    Triangle triangle({3.0, 10.0}, {4.0, 5.0}, {2.0, 3.0});
    triangle.move(4.0, 5.0);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, 2, EPS);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, 7, EPS);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, 7, EPS);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, 11.5, EPS);
    BOOST_CHECK_CLOSE(triangle.getArea(), 6, EPS);
  }

  BOOST_AUTO_TEST_CASE(Move_Delta)
  {
    Triangle triangle({3.0, 10.0}, {4.0, 5.0}, {2.0, 3.0});
    triangle.move({4.0, 5.0});
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, 2, EPS);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, 7, EPS);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, 4, EPS);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, 5.5, EPS);
    BOOST_CHECK_CLOSE(triangle.getArea(), 6, EPS);
  }

  BOOST_AUTO_TEST_CASE(getArea)
  {
    Triangle triangle({3.0, 10.0}, {4.0, 5.0}, {2.0, 3.0});
    BOOST_CHECK_CLOSE(triangle.getArea(), 6, EPS);
  }

  BOOST_AUTO_TEST_CASE(scale)
  {
    Triangle triangle({3.0, 10.0}, {4.0, 5.0}, {2.0, 3.0});
    triangle.scale(2.0);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().width, 4, EPS);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().height, 14, EPS);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.x, 3, EPS);
    BOOST_CHECK_CLOSE(triangle.getFrameRect().pos.y, 7, EPS);
    BOOST_CHECK_CLOSE(triangle.getArea(), 6 * 4, EPS);
    BOOST_CHECK_THROW(triangle.scale(-2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()




