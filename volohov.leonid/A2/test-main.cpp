#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include "circle.hpp"
#include "rectangle.hpp"
#include <stdexcept>
#include <cmath>
#include <boost/test/included/unit_test.hpp>

const double accuracy = 0.0001;

BOOST_AUTO_TEST_SUITE (Rectangle_Test)

  BOOST_AUTO_TEST_CASE (Rectangle_InvarienceTest)
  {
    volohov::Rectangle rectangle( {1.1, 2.2}, 3.3, 4.4 );
    double area_rectangle = rectangle.getArea();
    rectangle.move( {20.0, 20.0} );
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().width, 3.3);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().height, 4.4);
    BOOST_REQUIRE_EQUAL(rectangle.getArea(), area_rectangle);
    rectangle.move( 10.0, 10.0 );
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().width, 3.3);
    BOOST_REQUIRE_EQUAL(rectangle.getFrameRect().height, 4.4);
    BOOST_REQUIRE_EQUAL(rectangle.getArea(), area_rectangle);

  }

  BOOST_AUTO_TEST_CASE(Rectangle_ScaleTest)
  {
    volohov::Rectangle rectangle( {1.1, 2.2}, 3.3, 4.4 );
    double area_rectangle = rectangle.getArea();
    rectangle.scale(2.0);
    BOOST_REQUIRE_CLOSE_FRACTION(rectangle.getArea(), area_rectangle * pow(2.0, 2.0), accuracy);
  }

  BOOST_AUTO_TEST_CASE(Rectangle_InvalidParametersTest)
  {
    BOOST_CHECK_THROW(volohov::Rectangle rectangle( {1.1, 2.2}, -1.0, -2.0 ), std::invalid_argument);
    BOOST_CHECK_THROW(volohov::Rectangle rectangle( {1.1, 2.2}, 1.0, -2.0 ), std::invalid_argument);
    BOOST_CHECK_THROW(volohov::Rectangle rectangle( {1.1, 2.2}, -1.0, 2.0 ), std::invalid_argument);
    volohov::Rectangle rectangle( {1.1, 2.2}, 3.3, 4.4 );
    BOOST_CHECK_THROW(rectangle.scale(-1.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE (Circle_Test)

  BOOST_AUTO_TEST_CASE (Circle_InvarienceTest)
  {
    volohov::Circle circle( {1.0, 2.0}, 3.0);
    double area_circle = circle.getArea();
    circle.move( {20.0, 20.0} );
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().width, 6.0);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().height, 6.0);
    BOOST_REQUIRE_EQUAL(circle.getArea(), area_circle);
    circle.move( 30.0, 30.0 );
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().width, 6.0);
    BOOST_REQUIRE_EQUAL(circle.getFrameRect().height, 6.0);
    BOOST_REQUIRE_EQUAL(circle.getArea(), area_circle);
  }

  BOOST_AUTO_TEST_CASE(Circle_ScaleTest)
  {
    volohov::Circle circle( {1.0, 2.0}, 3.0);
    double area_circle = circle.getArea();
    circle.scale(4.0);
    BOOST_REQUIRE_CLOSE_FRACTION(circle.getArea(), area_circle * pow(4.0, 2.0), accuracy);
  }

  BOOST_AUTO_TEST_CASE(Circle_invalid_parameters_test)
  {
    BOOST_CHECK_THROW(volohov::Circle circle( {1.0, 2.0}, -1.0), std::invalid_argument);
    volohov::Circle circle( {1.0, 2.0}, 3.0);
    BOOST_CHECK_THROW(circle.scale(-2.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
