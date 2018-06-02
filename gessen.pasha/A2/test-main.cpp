#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"

const double ACCURACY = 0.0001;

BOOST_AUTO_TEST_SUITE (Rectangle_test)

  BOOST_AUTO_TEST_CASE (Rectangle_parameters_invarience_after_moving_test)
  {
    gessen::Rectangle rectangle( {8.0, 9.0}, 10.0, 6.0 );
    double area_rectangle = rectangle.getArea();
    rectangle.move( 15.1, 38.22 );
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().width, 10.0);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().height, 6.0);
    BOOST_REQUIRE_EQUAL(rectangle.getArea(), area_rectangle);
    rectangle.move( {14.0, 28.0} );
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().width, 10.0);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().height, 6.0);
    BOOST_REQUIRE_EQUAL(rectangle.getArea(), area_rectangle);
  }

  BOOST_AUTO_TEST_CASE(Rectangle_scale_test)
  {
    gessen::Rectangle rectangle( {8.0, 9.0}, 10.0, 6.0 );
    double area_rectangle = rectangle.getArea();
    rectangle.scale(2.0);
    BOOST_REQUIRE_CLOSE_FRACTION(rectangle.getArea(), area_rectangle * pow(2.0, 2.0), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(Rectangle_invalid_parameters_test)
  {
    BOOST_CHECK_THROW(gessen::Rectangle rectangle( {8.0, 9.0}, -68.0, -34.0 ), std::invalid_argument);
    BOOST_CHECK_THROW(gessen::Rectangle rectangle( {8.0, 9.0}, 68.0, -34.0 ), std::invalid_argument);
    BOOST_CHECK_THROW(gessen::Rectangle rectangle( {8.0, 9.0}, -68.0, 34.0 ), std::invalid_argument);
    gessen::Rectangle rectangle( {8.0, 9.0}, 10.0, 6.0 );
    BOOST_CHECK_THROW(rectangle.scale(-1.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE (Circle_test)

  BOOST_AUTO_TEST_CASE (Circle_parameters_invarience_after_moving_test)
  {
    gessen::Circle circle( {22.8, 32.2}, 10.0);
    double area_circle = circle.getArea();
    circle.move( 13.47, 123.4 );
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().width, 20.0);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().height, 20.0);
    BOOST_REQUIRE_EQUAL(circle.getArea(), area_circle);
    circle.move( {82.0, 64.0} );
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().width, 20.0);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().height, 20.0);
    BOOST_REQUIRE_EQUAL(circle.getArea(), area_circle);
  }

  BOOST_AUTO_TEST_CASE(Circle_scale_test)
  {
    gessen::Circle circle( {22.8, 32.2}, 10.0);
    double area_circle = circle.getArea();
    circle.scale(4.0);
    BOOST_REQUIRE_CLOSE_FRACTION(circle.getArea(), area_circle * pow(4.0, 2.0), ACCURACY);
  }

  BOOST_AUTO_TEST_CASE(Circle_invalid_parameters_test)
  {
    BOOST_CHECK_THROW(gessen::Circle circle( {22.8, 32.2}, -10.0), std::invalid_argument);
    gessen::Circle circle( {22.8, 32.2}, 10.0);
    BOOST_CHECK_THROW(circle.scale(-1.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()


