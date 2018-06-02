#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include <stdexcept>
#include "circle.hpp"
#include "rectangle.hpp"

const double ACCURACY = 0.0001;

BOOST_AUTO_TEST_SUITE (Rectangle_test)
  BOOST_AUTO_TEST_CASE (Rectangle_parameters_invarience_after_moving_test)
  {
    lysenko::Rectangle rectangle( {10.0, 12.0}, 8.0, 5.0 );
    double area_rectangle = rectangle.getArea();
    rectangle.move( 10.0, 35.0 );
    BOOST_REQUIRE_CLOSE(rectangle.getFrameRect().width, 8.0, ACCURACY);
    BOOST_REQUIRE_CLOSE(rectangle.getFrameRect().height, 5.0, ACCURACY);
    BOOST_REQUIRE_CLOSE(rectangle.getArea(), area_rectangle, ACCURACY);
    rectangle.move( {12.0, 22.0} );
    BOOST_REQUIRE_CLOSE(rectangle.getFrameRect().width, 8.0, ACCURACY);
    BOOST_REQUIRE_CLOSE(rectangle.getFrameRect().height, 5.0, ACCURACY);
    BOOST_REQUIRE_CLOSE(rectangle.getArea(), area_rectangle, ACCURACY);
  }
  BOOST_AUTO_TEST_CASE(Rectangle_scale_test)
  {
    lysenko::Rectangle rectangle( {10.0, 12.0}, 8.0, 5.0 );
    double area_rectangle = rectangle.getArea();
    rectangle.scale(2.0);
    BOOST_REQUIRE_CLOSE(rectangle.getArea(), area_rectangle * 2.0 * 2.0, ACCURACY);
  }
  BOOST_AUTO_TEST_CASE(Rectangle_invalid_parameters_test)
  {
    BOOST_CHECK_THROW(lysenko::Rectangle rectangle( {10.0, 12.0}, -40.0, -22.0 ), std::invalid_argument);
    BOOST_CHECK_THROW(lysenko::Rectangle rectangle( {10.0, 12.0}, 40.0, -22.0 ), std::invalid_argument);
    BOOST_CHECK_THROW(lysenko::Rectangle rectangle( {10.0, 12.0}, -40.0, 22.0 ), std::invalid_argument);
    lysenko::Rectangle rectangle( {10.0, 12.0}, 8.0, 5.0 );
    BOOST_CHECK_THROW(rectangle.scale(-3.0), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE (Circle_test)
  BOOST_AUTO_TEST_CASE (Circle_parameters_invarience_after_moving_test)
  {
    lysenko::Circle circle( {15.0, 35.0}, 5.0);
    double area_circle = circle.getArea();
    circle.move( 18.0, 54.0 );
    BOOST_REQUIRE_CLOSE(circle.getFrameRect().width, 10.0, ACCURACY);
    BOOST_REQUIRE_CLOSE(circle.getFrameRect().height, 10.0, ACCURACY);
    BOOST_REQUIRE_CLOSE(circle.getArea(), area_circle, ACCURACY);
    circle.move( {75.0, 65.0} );
    BOOST_REQUIRE_CLOSE(circle.getFrameRect().width, 10.0, ACCURACY);
    BOOST_REQUIRE_CLOSE(circle.getFrameRect().height, 10.0, ACCURACY);
    BOOST_REQUIRE_CLOSE(circle.getArea(), area_circle, ACCURACY);
  }
  BOOST_AUTO_TEST_CASE(Circle_scale_test)
  {
    lysenko::Circle circle( {15.0, 35.0}, 5.0);
    double area_circle = circle.getArea();
    circle.scale(3.0);
    BOOST_REQUIRE_CLOSE(circle.getArea(), area_circle * 3.0 * 3.0, ACCURACY);
  }
  BOOST_AUTO_TEST_CASE(Circle_invalid_parameters_test)
  {
    BOOST_CHECK_THROW(lysenko::Circle circle( {15.0, 35.0}, -5.0), std::invalid_argument);
    lysenko::Circle circle( {15.0, 35.0}, 5.0);
    BOOST_CHECK_THROW(circle.scale(-3.0), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()
