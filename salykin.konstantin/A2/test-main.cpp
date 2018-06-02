#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define EPS 0.00001

#include <boost/test/included/unit_test.hpp>

#include "rectangle.hpp"
#include "circle.hpp"

using namespace salykin;

BOOST_AUTO_TEST_SUITE(Circle_Test)
  BOOST_AUTO_TEST_CASE(Area_Move_Test_Circle)
  {
    Circle crcl(2.0, {7.6, 0.0});
    double oldArea = crcl.getArea();
    crcl.move(-1.0, 2.0);
    BOOST_REQUIRE_CLOSE_FRACTION(crcl.getArea(), oldArea, EPS);
    crcl.move({-1.0, 2.0});
    BOOST_REQUIRE_CLOSE_FRACTION(crcl.getArea(), oldArea, EPS);
  }

  BOOST_AUTO_TEST_CASE(Radius_Move_Test_Circle)
  {
    Circle crcl(2.0, {7.6, 0.0});
    double oldRadius = crcl.getRadius();
    crcl.move(-1.0, 2.0);
    BOOST_REQUIRE_CLOSE_FRACTION(crcl.getRadius(), oldRadius, EPS);
    crcl.move({-1.0, 2.0});
    BOOST_REQUIRE_CLOSE_FRACTION(crcl.getRadius(), oldRadius, EPS);
  }

  BOOST_AUTO_TEST_CASE(Area_Scale_Test_Circle)
  {
    Circle crcl(2.0, {7.6, 0.0});
    double oldArea = crcl.getArea();
    double mult = 5.0;
    crcl.scale(mult);
    BOOST_REQUIRE_CLOSE_FRACTION(crcl.getArea(), (oldArea * (mult * mult)), EPS);
  }

  BOOST_AUTO_TEST_CASE(Radius_Scale_Test_Circle)
  {
    Circle crcl(2.0, {7.6, 0.0});
    double oldRadius = crcl.getRadius();
    double mult = 10.0;
    crcl.scale(mult);
    BOOST_REQUIRE_CLOSE_FRACTION(crcl.getRadius(), (oldRadius * mult), EPS);
  }

  BOOST_AUTO_TEST_CASE(Inavalid_Argumend_Constructor_Test_Circle)
  {
    BOOST_CHECK_THROW(Circle(-1.0, {0.0, 0.0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_Scale_Test_Circle)
  {
    Circle crcl(4.0, {0.0, 0.0});
    BOOST_CHECK_THROW(crcl.scale(-1.0), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Rectangle_Tests)
  BOOST_AUTO_TEST_CASE(Area_Move_Test_Rectangle)
  {
    Rectangle rctngl(2.25, 9.7, {3.2, 3.4});
    double oldArea = rctngl.getArea();
    rctngl.move(10.0, 5.0);
    BOOST_REQUIRE_CLOSE_FRACTION(rctngl.getArea(), oldArea, EPS);
    rctngl.move({10.0, 5.0});
    BOOST_REQUIRE_CLOSE_FRACTION(rctngl.getArea(), oldArea, EPS);
  }

  BOOST_AUTO_TEST_CASE(Width_And_Height_Move_Test_Rectangle)
  {
    Rectangle rctngl(2.25, 9.7, {3.2, 3.4});
    double oldWidth = rctngl.getWidth();
    double oldHeight = rctngl.getHeight();
    rctngl.move(10.0, 24.0);
    BOOST_REQUIRE_CLOSE_FRACTION(rctngl.getWidth(), oldWidth, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(rctngl.getHeight(), oldHeight, EPS);
    rctngl.move({10.0, 24.0});
    BOOST_REQUIRE_CLOSE_FRACTION(rctngl.getWidth(), oldWidth, EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(rctngl.getHeight(), oldHeight, EPS);
  }

  BOOST_AUTO_TEST_CASE(Area_Scale_Test_Rectangle)
  {
    Rectangle rctngl(2.25, 9.7, {3.2, 3.4});
    double oldArea = rctngl.getArea();
    double mult = 10.0;
    rctngl.scale(mult);
    BOOST_REQUIRE_CLOSE_FRACTION(rctngl.getArea(), (oldArea * (mult * mult)), EPS);
  }

  BOOST_AUTO_TEST_CASE(Width_And_Height_Scale_Test_Rectangle)
  {
    Rectangle rctngl(2.25, 9.7, {3.2, 3.4});
    double oldWidth = rctngl.getWidth();
    double oldHeight = rctngl.getHeight();
    double mult = 10.0;
    rctngl.scale(mult);
    BOOST_REQUIRE_CLOSE_FRACTION(rctngl.getWidth(), (oldWidth * mult), EPS);
    BOOST_REQUIRE_CLOSE_FRACTION(rctngl.getHeight(), (oldHeight * mult), EPS);
  }

  BOOST_AUTO_TEST_CASE(Inavalid_Argumend_Constructor_Test_Rectangle)
  {
    BOOST_CHECK_THROW(Rectangle(-1, -1, {0.0, 0.0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_Scale_Test_Rectangle)
  {
    Rectangle rctngl(1, 1, {0.0, 0.0});
    BOOST_CHECK_THROW(rctngl.scale(-1.0), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()
