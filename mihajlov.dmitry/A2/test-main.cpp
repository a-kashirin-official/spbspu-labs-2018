#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"

const double precision = 1e-3;

BOOST_AUTO_TEST_SUITE(RectangleTest)

  BOOST_AUTO_TEST_CASE(InvalidConstructorParams)
  {
    BOOST_CHECK_THROW(mihajlov::Rectangle({10.0, 10.0}, -2.2, 5.0), std::invalid_argument);
    BOOST_CHECK_THROW(mihajlov::Rectangle({10.0, 10.0}, 0.0, -7.46), std::invalid_argument);
    BOOST_CHECK_THROW(mihajlov::Rectangle({10.0, 10.0}, -32.12, -3.4), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    mihajlov::Rectangle rectangle({0.0, 0.0}, 10.3, 5.9);
    const double areaBeforeMoving = rectangle.getArea();
    const mihajlov::rectangle_t rectBeforeMoving  = rectangle.getFrameRect();

    rectangle.move({100.0, 100.0});

    BOOST_CHECK_CLOSE_FRACTION(areaBeforeMoving, rectangle.getArea(), precision);
    BOOST_CHECK_CLOSE_FRACTION(rectBeforeMoving.height, rectangle.getFrameRect().height, precision);
    BOOST_CHECK_CLOSE_FRACTION(rectBeforeMoving.width, rectangle.getFrameRect().width, precision);

  }

  BOOST_AUTO_TEST_CASE(MoveByShifting)
  {
    mihajlov::Rectangle rectangle({0.0, 0.0}, 3.0, 14.53);
    const double areaBeforeMoving = rectangle.getArea();
    const mihajlov::rectangle_t rectBerofeMoving = rectangle.getFrameRect();

    rectangle.move(10.42, 4.66);

    BOOST_CHECK_CLOSE_FRACTION(areaBeforeMoving, rectangle.getArea(), precision);
    BOOST_CHECK_CLOSE_FRACTION(rectBerofeMoving.height, rectangle.getFrameRect().height, precision);
    BOOST_CHECK_CLOSE_FRACTION(rectBerofeMoving.width, rectangle.getFrameRect().width, precision);

  }

  BOOST_AUTO_TEST_CASE(ScallingObject)
  {
    mihajlov::Rectangle rectangle({10.0, 10.0}, 20.0, 30.0);
    const double areaBeforeScalling = rectangle.getArea();
    const double multiplier = 2.5;

    rectangle.scale(multiplier);

    BOOST_CHECK_CLOSE(multiplier*multiplier*areaBeforeScalling, rectangle.getArea(), precision);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTest)

  BOOST_AUTO_TEST_CASE(InvalidConstructorParams)
  {
    BOOST_CHECK_NO_THROW(mihajlov::Circle({10.0, 10.0}, 0.0));
    BOOST_CHECK_THROW(mihajlov::Circle({10.0, 10.0}, -3.53), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    mihajlov::Circle circle({0.0, 0.0}, 20.0);

    const double areaBeforeMoving = circle.getArea();
    const mihajlov::rectangle_t frameBeforeMoving = circle.getFrameRect();

    circle.move({30.0, 30.0});

    BOOST_CHECK_CLOSE_FRACTION(areaBeforeMoving, circle.getArea(), precision);
    BOOST_CHECK_CLOSE_FRACTION(frameBeforeMoving.width, circle.getFrameRect().width, precision);
    BOOST_CHECK_CLOSE_FRACTION(frameBeforeMoving.height, circle.getFrameRect().height, precision);
  }

  BOOST_AUTO_TEST_CASE(MoveByShifting)
  {
    mihajlov::Circle circle({10.0, 10.0}, 50.0);

    const double areaBeforeMoving = circle.getArea();
    const mihajlov::rectangle_t rectBeforeMoving = circle.getFrameRect();

    circle.move(32.54, -3.43);

    BOOST_CHECK_CLOSE_FRACTION(areaBeforeMoving, circle.getArea(), precision);
    BOOST_CHECK_CLOSE_FRACTION(rectBeforeMoving.height, circle.getFrameRect().height, precision);
    BOOST_CHECK_CLOSE_FRACTION(rectBeforeMoving.width, circle.getFrameRect().width, precision);
  }

  BOOST_AUTO_TEST_CASE(ScallingObject)
  {
    mihajlov::Circle circle({0.0, 0.0}, 10.0);
    const double areaBeforeScalling = circle.getArea();
    const double multiplier = 2.5;

    circle.scale(multiplier);

    BOOST_CHECK_CLOSE(multiplier*multiplier*areaBeforeScalling, circle.getArea(), precision);
  }

BOOST_AUTO_TEST_SUITE_END()
