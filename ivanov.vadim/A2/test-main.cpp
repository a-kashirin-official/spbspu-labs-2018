#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "circle.hpp"
#include "rectangle.hpp"

const double EPS = 1e-9;

BOOST_AUTO_TEST_SUITE (TestRectangle)
  BOOST_AUTO_TEST_CASE (ParametersOfRectangle)
  {
    ivanov::Rectangle Rectangle({{10.0, 20.0}, 30.0, 20.0});
    ivanov::rectangle_t value = Rectangle.getFrameRect();
    double area = Rectangle.getArea();
    Rectangle.move({10.0, 40.0});
    BOOST_REQUIRE_EQUAL (value.height, Rectangle.getFrameRect().height);
    BOOST_REQUIRE_EQUAL (value.width, Rectangle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL (area, Rectangle.getArea());
    Rectangle.move(10.0, 40.0);
    BOOST_REQUIRE_EQUAL (value.height, Rectangle.getFrameRect().height);
    BOOST_REQUIRE_EQUAL (value.width, Rectangle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL (area, Rectangle.getArea());
  }

  BOOST_AUTO_TEST_CASE (ScalingAreaOfRectangle)
  {
    ivanov::Rectangle Rectangle({{10.0, 20.0}, 30.0, 20.0});
    double area = Rectangle.getArea();
    Rectangle.scale(3.0);
    BOOST_REQUIRE_CLOSE_FRACTION (Rectangle.getArea(), area * 3.0 * 3.0, EPS);
  }

  BOOST_AUTO_TEST_CASE (InvalidArgumentsOfRectangle)
  {
    BOOST_CHECK_THROW (ivanov::Rectangle({{10.0, 20.0}, -30.0, 20.0}), std::invalid_argument);
    BOOST_CHECK_THROW (ivanov::Rectangle({{10.0, 20.0}, 30.0, -20.0}), std::invalid_argument);
    BOOST_CHECK_THROW (ivanov::Rectangle({{10.0, 20.0}, -30.0, -20.0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE (InvalidScaleOfRectangle)
  {
    ivanov::Rectangle Rectangle({{10.0, 20.0}, 30.0, 20.0});
    BOOST_CHECK_THROW (Rectangle.scale(-3.0), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE (TestCircle)
  BOOST_AUTO_TEST_CASE (ParametersOfCircle)
  {
    ivanov::Circle Circle({{10.0, 20.0}, 30.0});
    ivanov::rectangle_t value = Circle.getFrameRect();
    double area = Circle.getArea();
    Circle.move(10.0, 40.0);
    BOOST_REQUIRE_EQUAL (value.height, Circle.getFrameRect().height);
    BOOST_REQUIRE_EQUAL (value.width, Circle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL (area, Circle.getArea());
    Circle.move({10.0, 40.0});
    BOOST_REQUIRE_EQUAL (value.height, Circle.getFrameRect().height);
    BOOST_REQUIRE_EQUAL (value.width, Circle.getFrameRect().width);
    BOOST_REQUIRE_EQUAL (area, Circle.getArea());
  }

  BOOST_AUTO_TEST_CASE (ScalingAreaOfCircle)
  {
    ivanov::Circle Circle({{10.0, 20.0}, 30.0});
    double area = Circle.getArea();
    Circle.scale(3.0);
    BOOST_REQUIRE_CLOSE_FRACTION (Circle.getArea(), area * 3.0 * 3.0, EPS);
  }

  BOOST_AUTO_TEST_CASE (InvalidArgumentsOfCircle)
  {
    BOOST_CHECK_THROW (ivanov::Circle({{10.0, 20.0}, -30.0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE (InvalidScaleOfCircle)
  {
    ivanov::Circle Circle({{10.0, 20.0}, 30.0});
    BOOST_CHECK_THROW (Circle.scale(-3.0), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()
