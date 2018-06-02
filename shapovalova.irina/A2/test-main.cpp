#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"

const double EPS_TEST = 0.0001;

BOOST_AUTO_TEST_SUITE(RectangleTests)
  BOOST_AUTO_TEST_CASE(ImmutableParametersOfRectanle)
  {
    shapovalova::Rectangle rectangle ({{20.0, 10.0}, 20.0, 40.0});
    shapovalova::rectangle_t frame = rectangle.getFrameRect();
    double area = rectangle.getArea();
    rectangle.move({10, -10});
    BOOST_REQUIRE_EQUAL(frame.width, rectangle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(frame.height, rectangle.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(area, rectangle.getArea());
  }

  BOOST_AUTO_TEST_CASE(ScaleChangeAreaOfRectangle)
  {
    shapovalova::Rectangle rectangle ({{20.0, 10.0}, 20.0, 40.0});
    double area = rectangle.getArea();
    rectangle.scale(2.0);
    BOOST_REQUIRE_CLOSE_FRACTION(rectangle.getArea(), area * 2.0 * 2.0, EPS_TEST);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentsOfRectangle)
  {
    BOOST_CHECK_THROW(shapovalova::Rectangle ({{20.0, 10.0}, 20.0, -40.0}), std::invalid_argument);
    BOOST_CHECK_THROW(shapovalova::Rectangle ({{20.0, 10.0}, -20.0, 40.0}), std::invalid_argument);
    BOOST_CHECK_THROW(shapovalova::Rectangle ({{20.0, 10.0}, -20.0, -40.0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentOfScale)
  {
    shapovalova::Rectangle rectangle ({{20.0, 10.0}, 20.0, 40.0});
    BOOST_CHECK_THROW(rectangle.scale(-2.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTests)
  BOOST_AUTO_TEST_CASE(ImmutableParametersOfCircle)
  {
    shapovalova::Circle circle ({20, 10}, 20.0);
    shapovalova::rectangle_t frame = circle.getFrameRect();
    double area = circle.getArea();
    circle.move(10, -10);
    BOOST_REQUIRE_EQUAL(frame.width, circle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL(frame.height, circle.getFrameRect().height);
    BOOST_REQUIRE_EQUAL(area, circle.getArea());
  }

  BOOST_AUTO_TEST_CASE(ScaleChangeAreaOfCircle)
  {
    shapovalova::Circle circle ({20, 10}, 20.0);
    double area = circle.getArea();
    circle.scale(2.0);
    BOOST_REQUIRE_CLOSE_FRACTION(circle.getArea(), area * 2.0 * 2.0, EPS_TEST);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentsOfCircle)
  {
    BOOST_CHECK_THROW(shapovalova::Circle circle ({20, 10}, -20.0), std::invalid_argument)
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentOfScale)
  {
    shapovalova::Circle circle ({20, 10}, 20.0);
    BOOST_CHECK_THROW(circle.scale(-2.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

