#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <cmath>
#include <iostream>
#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"

const double EPSILON = 0.001;
const grigorev::point_t DOT={5.3, 6.3};

BOOST_AUTO_TEST_SUITE(TestRectanlge)

  BOOST_AUTO_TEST_CASE(InvalidArgumentsRectangleWH)
  {
    BOOST_CHECK_THROW(grigorev::Rectangle rectangle({2.0, 2.0}, -10.3, -6.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentRectangleW)
  {
    BOOST_CHECK_THROW(grigorev::Rectangle rectangle({2.0, 2.0}, -10.3, 6.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentRectangleH)
  {
    BOOST_CHECK_THROW(grigorev::Rectangle rectangle({2.0, 2.0}, 10.3, -6.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(RectangleParametrsAfterMovingToPoint)
  {
    grigorev::Rectangle rectangle({2.5, 3.5}, 10.0, 5.0);
    rectangle.move(DOT);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 10.0, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 5.0, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getArea(), 50.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(RectangleParametrsAfterMovingDxDy)
  {
    grigorev::Rectangle rectangle({2.5, 3.5}, 11.0, 6.0);
    rectangle.move(3.0, 5.7);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, 11.0, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, 6.0, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getArea(), 66.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidRectangleScale)
  {
    grigorev::Rectangle rectangle({3.0, 3.0}, 10.0, 1.0);
    BOOST_CHECK_THROW(rectangle.scale(-5.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(AreaAfterRectangleScale)
  {
    grigorev::Rectangle rectangle({3.0, 3.0}, 10.0, 2.0);
    rectangle.scale(2.0);
    BOOST_CHECK_CLOSE(rectangle.getArea(), 80.0, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestCircle)

  BOOST_AUTO_TEST_CASE(InvalidArgumentCircleR)
  {
    BOOST_CHECK_THROW(grigorev::Circle circle({2.2, 2.3 }, -6.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(CircleParametrsAfterMovingToPoint)
  {
    grigorev::Circle circle({2.5, 3.5}, 10.0);
    circle.move(DOT);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, 20.0, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, 20.0, EPSILON);
    BOOST_CHECK_CLOSE(circle.getArea(), 10.0 * 10.0 * M_PI, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(CircleParametrsAfterMovingDxDy)
  {
    grigorev::Circle circle({2.5, 3.5}, 11.0);
    circle.move(3.0, 5.7);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, 22.0, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, 22.0, EPSILON);
    BOOST_CHECK_CLOSE(circle.getArea(), 11.0 * 11.0 * M_PI, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidCircleScale)
  {
    grigorev::Circle circle({3.0, 3.0}, 10.0);
    BOOST_CHECK_THROW(circle.scale(-5.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(AreaAfterRectangleScale)
  {
    grigorev::Circle circle({3.0, 3.0}, 10.0);
    circle.scale(2.0);
    BOOST_CHECK_CLOSE(circle.getArea(), 10.0 * 10.0 * 2.0 * 2.0 * M_PI, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END()
