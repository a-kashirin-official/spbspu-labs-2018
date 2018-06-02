#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include <stdexcept>
#include <circle.hpp>
#include <rectangle.hpp>

using namespace zasyadko;
const double EPSILON = 0.0001;
BOOST_AUTO_TEST_SUITE(CircleTesting)

  BOOST_AUTO_TEST_CASE(MoveByXYTest)
  {
    Circle testCircle({10,10},20);
    testCircle.move(15,15);
    BOOST_REQUIRE_EQUAL(testCircle.getRadius(),20);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getArea(),400*M_PI,EPSILON);
  }
  BOOST_AUTO_TEST_CASE(MoveToXYPointTest)
  {
    Circle testCircle({10,10},20);
    testCircle.move({20,20});
    BOOST_REQUIRE_EQUAL(testCircle.getRadius(),20);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getArea(),400*M_PI,EPSILON);
  }
  BOOST_AUTO_TEST_CASE(AreaScaleTest)
  {
    Circle testCircle({10,10},20);
    testCircle.scale(2);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getArea(),400*4*M_PI,EPSILON);
  }
  BOOST_AUTO_TEST_CASE(InvalidScaleCircleTest)
  {
    Circle testCircle({10,10},20);
    BOOST_CHECK_THROW(testCircle.scale(-2),std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(InvalidInitCircleTest)
  {
    BOOST_CHECK_THROW(Circle({10,10},-20),std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(RectangleTest)

  BOOST_AUTO_TEST_CASE(MoveByXYTest)
  {
    Rectangle testRect({10,10},15,20);
    testRect.move(10,10);
    BOOST_REQUIRE_EQUAL(testRect.getFrameRect().width,20);
    BOOST_REQUIRE_EQUAL(testRect.getFrameRect().height,15);
    BOOST_CHECK_CLOSE_FRACTION(testRect.getArea(),300,EPSILON);
  }
  BOOST_AUTO_TEST_CASE(MoveToXYPointTest)
  {
    Rectangle testRect({10,10},15,20);
    testRect.move({10,10});
    BOOST_REQUIRE_EQUAL(testRect.getFrameRect().width,20);
    BOOST_REQUIRE_EQUAL(testRect.getFrameRect().height,15);
    BOOST_CHECK_CLOSE_FRACTION(testRect.getArea(),300,EPSILON);
  }
  BOOST_AUTO_TEST_CASE(AreaScaleTest)
  {
    Rectangle testRect({10,10},15,20);
    testRect.scale(2);
    BOOST_CHECK_CLOSE_FRACTION(testRect.getArea(),300*4,EPSILON);
  }
  BOOST_AUTO_TEST_CASE(InvalidScaleRectTest)
  {
    Rectangle testRect({10,10},15,20);
    BOOST_CHECK_THROW(testRect.scale(-2),std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(InvalidArgsTest)
  {
    BOOST_CHECK_THROW(Rectangle({10,10},-15,20),std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle({10,10},15,-20),std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END();
