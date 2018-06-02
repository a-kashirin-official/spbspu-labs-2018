#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#define EPS 0.001

#include "rectangle.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>


using namespace orlov;

BOOST_AUTO_TEST_SUITE(Rectangle_Tests)

  BOOST_AUTO_TEST_CASE(Absolute_Move_Test_Rect)
  {
    Rectangle rect({ 10.9, 5.5, { 11.1, 15.6 } });
    rect.move( { 53.3, 20.4 } );
    BOOST_CHECK(rect.getFrameRect().pos.x == 53.3 && rect.getFrameRect().pos.y == 20.4);
  }

  BOOST_AUTO_TEST_CASE(Relative_Move_Test_Rect)
  {
    Rectangle rect({ 10.9, 5.5, { 11.1, 15.6 } });
    rect.move(-10.1, 0.4);
    BOOST_CHECK_CLOSE_FRACTION(rect.getPos().x, 1.0, EPS);
    BOOST_CHECK_CLOSE_FRACTION(rect.getPos().y, 16.0, EPS);
  }

  BOOST_AUTO_TEST_CASE(Area_Test_Rect)
  {
    Rectangle rect({ 5, 5, { 11.1, 15.6 } });
    BOOST_REQUIRE_EQUAL(rect.getArea(), 25);
  }

  BOOST_AUTO_TEST_CASE(Area_Test_With_Move_Rect)
  {
    Rectangle rect({ 5, 5, { 11.1, 15.6 } });
    rect.move(10, 5);
    BOOST_REQUIRE_EQUAL(rect.getArea(), 25);
  }

  BOOST_AUTO_TEST_CASE(Height_Test_Rect)
  {
    Rectangle rect({ 5, 5, { 11.1, 15.6 } });
    rect.move(10, 0);
    BOOST_REQUIRE_EQUAL(rect.getFrameRect().height, 5);
  }

  BOOST_AUTO_TEST_CASE(Widht_Test_Rect)
  {
    Rectangle rect({ 5, 5, { 11.1, 15.6 } });
    rect.move(10, 0);
    BOOST_REQUIRE_EQUAL(rect.getFrameRect().width, 5);
  }

  BOOST_AUTO_TEST_CASE(Frame_Rect_Test_Rect)
  {
    Rectangle rect({ 5, 5, { 11.1, 15.6 } });
    BOOST_REQUIRE_EQUAL(rect.getFrameRect().width, 5);
    BOOST_REQUIRE_EQUAL(rect.getFrameRect().height, 5);
    BOOST_REQUIRE_EQUAL(rect.getFrameRect().pos.x, 11.1);
    BOOST_REQUIRE_EQUAL(rect.getFrameRect().pos.y, 15.6);
  }

  BOOST_AUTO_TEST_CASE(Scale_Test_Rect)
  {
    Rectangle rect({ 5, 5, { 0, 0 } });
    rect.scale(10);
    BOOST_REQUIRE_EQUAL(rect.getArea(), 25 * 100);
  }

  BOOST_AUTO_TEST_CASE(Inavalid_Argumend_Constructor_Test_Rect)
  {
    BOOST_CHECK_THROW(Rectangle({ -1, -1, { 0, 0 } }), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_Scale_Test_Rect)
  {
    Rectangle rect({ 5, 5, { 0, 0 } });
    BOOST_CHECK_THROW(rect.scale(-1), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Circle_Test)

  BOOST_AUTO_TEST_CASE(Absolute_Move_Test_Circle)
  {
    Circle circ(10, { 10, 0 });
    circ.move( { 15, 20} );
    BOOST_CHECK(circ.getPos().x == 15 && circ.getPos().y == 20);
  }

  BOOST_AUTO_TEST_CASE(Relative_Move_Test_Circle)
  {
    Circle circ(10, { 10, 0 });
    circ.move(-5, 8);
    BOOST_CHECK_CLOSE_FRACTION(circ.getPos().x, 5, EPS);
    BOOST_CHECK_CLOSE_FRACTION(circ.getPos().y, 8, EPS);
  }

  BOOST_AUTO_TEST_CASE(Area_Test_Circle)
  {
    Circle circ(10, { 10, 0 });
    BOOST_REQUIRE_EQUAL(circ.getArea(), 100 * M_PI);
  }

  BOOST_AUTO_TEST_CASE(Area_Test_With_Move_Circle)
  {
    Circle circ(10, { 10, 0 });
    circ.move(10, 5);
    BOOST_REQUIRE_EQUAL(circ.getArea(), 100 * M_PI);
  }

  BOOST_AUTO_TEST_CASE(Radius_Test_Circle)
  {
    Circle circ(10, { 10, 0 });
    circ.move(0, 10);
    BOOST_REQUIRE_EQUAL((circ.getFrameRect().width / 2), 10);
  }

  BOOST_AUTO_TEST_CASE(Scale_Test_Circle)
  {
    Circle circ(10, { 10, 0 });
    circ.scale(2);
    BOOST_REQUIRE_EQUAL(circ.getArea(), 100 * M_PI * 4);
  }

  BOOST_AUTO_TEST_CASE(Frame_Rect_Test_Circle)
  {
    Circle circ(15, { 3, 0 });
    BOOST_REQUIRE_EQUAL(circ.getFrameRect().width, 30);
    BOOST_REQUIRE_EQUAL(circ.getFrameRect().height, 30);
    BOOST_REQUIRE_EQUAL(circ.getFrameRect().pos.x, 3);
    BOOST_REQUIRE_EQUAL(circ.getFrameRect().pos.y, 0);
  }

  BOOST_AUTO_TEST_CASE(Inavalid_Argumend_Constructor_Test_Circle)
  {
    BOOST_CHECK_THROW(Circle(-1, { 0, 0 }), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_Scale_Test_Circle)
  {
    Circle circ(10, { 0, 0 });
    BOOST_CHECK_THROW(circ.scale(-1), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Triangle_Tests)

  BOOST_AUTO_TEST_CASE(Absolute_Move_Test_Triangle)
  {
    Triangle trngl({ 10.6, 13.2 }, { 15.2, 18.0 }, { 11.1, 15.6 });
    trngl.move( { 53.3, 20.4 } );
    BOOST_CHECK_CLOSE_FRACTION(trngl.getPos().x, 53.3, EPS);
    BOOST_CHECK_CLOSE_FRACTION(trngl.getPos().y, 20.4, EPS);
  }

  BOOST_AUTO_TEST_CASE(Relative_Move_Test_Triangle)
  {
    Triangle trngl({ 10.6, 13.2 }, { 15.2, 18.0 }, { 11.1, 15.6 });
    trngl.move(-10.1, 0.4);
    BOOST_CHECK_CLOSE_FRACTION(trngl.getPos().x, 2.2, EPS);
    BOOST_CHECK_CLOSE_FRACTION(trngl.getPos().y, 16.0, EPS);
  }

  BOOST_AUTO_TEST_CASE(Area_Test_Triangle)
  {
    Triangle trngl({ 10.4, 13.2 }, { 15.3, 18.13 }, { 11.1, 15.6 });
    BOOST_CHECK_CLOSE_FRACTION(trngl.getArea(), 4.155, EPS);
  }

  BOOST_AUTO_TEST_CASE(Area_Test_With_Move_Triangle)
  {
    Triangle trngl({ 10.4, 13.2 }, { 15.3, 18.13 }, { 11.1, 15.6 });
    trngl.move(10, 5);
    BOOST_CHECK_CLOSE_FRACTION(trngl.getArea(), 4.155, EPS);
  }

  BOOST_AUTO_TEST_CASE(Frame_Rect_Test_Triangle)
  {
    Triangle trngl({ 10.4, 13.2 }, { 15.3, 18.13 }, { 11.1, 15.6 });
    BOOST_REQUIRE_EQUAL(trngl.getFrameRect().width, 4.9);
    BOOST_REQUIRE_EQUAL(trngl.getFrameRect().height, 4.93);
    BOOST_CHECK_CLOSE_FRACTION(trngl.getFrameRect().pos.x, 12.85, EPS);
    BOOST_CHECK_CLOSE_FRACTION(trngl.getFrameRect().pos.y, 15.665, EPS);
  }

  BOOST_AUTO_TEST_CASE(Scale_Test_Triangle)
  {
    Triangle trngl({ 0.0, 2.0 }, { -2.0, -1.0 }, { 2.0, -1.0 });
    trngl.scale(3.0);
    BOOST_CHECK_CLOSE_FRACTION(trngl.getArea(), 54, EPS);
  }

  BOOST_AUTO_TEST_CASE(Inavalid_Argumend_Constructor_Test_Triangle)
  {
    BOOST_CHECK_THROW(Triangle({ 0, 0 }, { -2, 0 }, { 2, 0 }), std::invalid_argument);
    BOOST_CHECK_THROW(Triangle({ -2, 0 }, { 0, 0 }, { 2, 0 }), std::invalid_argument);
    BOOST_CHECK_THROW(Triangle({ -2, 0 }, { 2, 0 }, { 0, 0 }), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Invalid_Argument_Scale_Test_Triangle)
  {
    Triangle trngl({ 10.6, 13.2 }, { 15.2, 18.0 }, { 11.1, 15.6 });
    BOOST_CHECK_THROW(trngl.scale(-1), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
