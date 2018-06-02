#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>
#include "rectangle.hpp"
#include "circle.hpp"

const double DELTA = 0.001;

using namespace krasilnikov;

BOOST_AUTO_TEST_SUITE(Rectangle_Tests)

BOOST_AUTO_TEST_CASE(Absolute_Move_Rectangle)
{
  Rectangle rect(11.9, 11.8, {17, 18} );
  rect.move({13.1, -2.1});
  BOOST_REQUIRE_EQUAL(rect.getPosition().x, 13.1);
  BOOST_REQUIRE_EQUAL(rect.getPosition().y, -2.1);
}

BOOST_AUTO_TEST_CASE(Relative_Move_Rectangle)
{
  Rectangle rect(11.9, 11.8, {17.1, 18.2} );
  rect.move(-16.1, -0.2);
  BOOST_CHECK_CLOSE_FRACTION(rect.getPosition().x, 1.0, DELTA);
  BOOST_CHECK_CLOSE_FRACTION(rect.getPosition().y, 18.0, DELTA);
}

BOOST_AUTO_TEST_CASE(Area_Rectangle)
{
  Rectangle rect(7, 7, {12.4, 13.2});
  BOOST_CHECK_CLOSE_FRACTION(rect.getArea(), 49, DELTA);
}

BOOST_AUTO_TEST_CASE(Area_Move_Rectangle)
{
  Rectangle rect(7, 7, {12.4, 13.2});
  rect.move(13, 7);
  BOOST_CHECK_CLOSE_FRACTION(rect.getArea(), 49, DELTA);
}

BOOST_AUTO_TEST_CASE(Height_Rectangle)
{
  Rectangle rect(7, 7, {12.4, 13.2});
  rect.move(13, 0);
  BOOST_REQUIRE_EQUAL(rect.getHeight(), 7);
}

BOOST_AUTO_TEST_CASE(Width_Rectangle)
{
  Rectangle rect(7, 7, {12.4, 13.2});
  rect.move(13, 0);
  BOOST_REQUIRE_EQUAL(rect.getWidth(), 7);
}

BOOST_AUTO_TEST_CASE(FrameRect_Rectangle)
{
  Rectangle rect(7, 7, {12.4, 13.2});
  BOOST_REQUIRE_EQUAL(rect.getFrameRect().height, 7);
  BOOST_REQUIRE_EQUAL(rect.getFrameRect().width, 7);
  BOOST_REQUIRE_EQUAL(rect.getFrameRect().pos.x, 12.4);
  BOOST_REQUIRE_EQUAL(rect.getFrameRect().pos.y, 13.2);
}

BOOST_AUTO_TEST_CASE(Scale_Rectangle)
{
  Rectangle rect(7, 7, {0, 0});
  rect.scale(5);
  BOOST_REQUIRE_EQUAL(rect.getArea(), 49 * 25);
}

BOOST_AUTO_TEST_CASE(Invalid_Argument_Constructor_Rectangle)
{
  BOOST_CHECK_THROW(Rectangle(-1, 1, {0, 0}), std::invalid_argument);
  BOOST_CHECK_THROW(Rectangle(1, -1, {0, 0}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(Invalid_Argument_Scale_Rectangle)
{
  Rectangle rect(7, 7, {0, 0});
  BOOST_CHECK_THROW(rect.scale(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Circle_Test)

BOOST_AUTO_TEST_CASE(Absolute_Move_Circle)
{
  Circle circ( {13, 7}, 10);
  circ.move( {7, 13});
  BOOST_REQUIRE_EQUAL(circ.getPosition().x, 7);
  BOOST_REQUIRE_EQUAL(circ.getPosition().y, 13);
}

BOOST_AUTO_TEST_CASE(Realtive_Move_Circle)
{
  Circle circ( {13, 7}, 10);
  circ.move(7, 13);
  BOOST_CHECK_CLOSE_FRACTION(circ.getPosition().x, 20, DELTA);
  BOOST_CHECK_CLOSE_FRACTION(circ.getPosition().y, 20, DELTA);
}

BOOST_AUTO_TEST_CASE(Area_Circle)
{
  Circle circ( {13, 7}, 10);
  BOOST_CHECK_CLOSE_FRACTION(circ.getArea(), 100 * M_PI, DELTA);
}

BOOST_AUTO_TEST_CASE(Area_Move_Circle)
{
  Circle circ( {13, 7}, 10);
  circ.move(7, 13);
  BOOST_CHECK_CLOSE_FRACTION(circ.getArea(), 100 * M_PI, DELTA);
}

BOOST_AUTO_TEST_CASE(Radius_Circle)
{
  Circle circ( {13, 7}, 10);
  circ.move(7, 13);
  BOOST_REQUIRE_EQUAL(circ.getRadius(), 10);
}

BOOST_AUTO_TEST_CASE(Scale_Circle)
{
  Circle circ( {13, 7}, 10);
  circ.scale(5);
  BOOST_CHECK_CLOSE_FRACTION(circ.getArea(), 100 * M_PI * 25, DELTA);
}

BOOST_AUTO_TEST_CASE(FrameRect_Circle)
{
  Circle circ( {13, 7}, 10);
  BOOST_REQUIRE_EQUAL(circ.getFrameRect().height, 20);
  BOOST_REQUIRE_EQUAL(circ.getFrameRect().width, 20);
  BOOST_REQUIRE_EQUAL(circ.getFrameRect().pos.x, 13);
  BOOST_REQUIRE_EQUAL(circ.getFrameRect().pos.y, 7);
}

BOOST_AUTO_TEST_CASE(Invalid_Argument_Constructor_Circle)
{
  BOOST_CHECK_THROW(Circle( {0, 0}, -1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(Invalid_Argument_Scale_Circle)
{
  Circle circ( {0, 0}, 10);
  BOOST_CHECK_THROW(circ.scale(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
