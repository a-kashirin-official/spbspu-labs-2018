#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include <stdexcept>
#include <circle.hpp>
#include <rectangle.hpp>

using namespace vasilev;
const double EPSILON = 0.0001;
BOOST_AUTO_TEST_SUITE(CircleTest)

  BOOST_AUTO_TEST_CASE(XYMoveTest)
  {
    Circle testCircle(20, {100, 100});
    testCircle.move(50, 50);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getFrameRect().pos.x, 150, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getFrameRect().pos.y, 150, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getRadius(), 20, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getArea(), 400*M_PI, EPSILON);
  }
  BOOST_AUTO_TEST_CASE(PointMoveTest)
  {
    Circle testCircle(20, {100, 100});
    testCircle.move({150, 150});
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getFrameRect().pos.x, 150, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getFrameRect().pos.y, 150, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getRadius(), 20, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getArea(), 400*M_PI, EPSILON);
  }
  BOOST_AUTO_TEST_CASE(ScaleTest)
  {
    Circle testCircle(20, {100, 100});
    testCircle.scale(2);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getArea(), 400*4*M_PI, EPSILON);
  }
  BOOST_AUTO_TEST_CASE(MultiplierTest)
  {
    Circle testCircle(20, {10, 10});
    BOOST_CHECK_THROW(testCircle.scale(-2), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(InitValuesTest)
  {
    BOOST_CHECK_THROW(Circle(-20, {100, 100}), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleTest)

  BOOST_AUTO_TEST_CASE(XYMoveTest)
  {
    Rectangle testRectangle(40, 20, {100, 100});
    testRectangle.move(50, 50);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getFrameRect().pos.x, 150, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getFrameRect().pos.y, 150, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getFrameRect().height, 20, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getFrameRect().width, 40, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getArea(), 800, EPSILON);
  }
  BOOST_AUTO_TEST_CASE(PointMoveTest)
  {
    Rectangle testRectangle(40, 20, {100, 100});
    testRectangle.move({150, 150});
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getFrameRect().pos.x, 150, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getFrameRect().pos.y, 150, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getFrameRect().height, 20, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getFrameRect().width, 40, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getArea(), 800, EPSILON);
  }
  BOOST_AUTO_TEST_CASE(ScaleTest)
  {
    Rectangle testRectangle(40, 20, {100, 100});
    testRectangle.scale(2);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getArea(), 800*4, EPSILON);
  }
  BOOST_AUTO_TEST_CASE(MultiplierTest)
  {
    Rectangle testRectangle(40, 20, {100, 100});
    BOOST_CHECK_THROW(testRectangle.scale(-2), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(InitValuesTest)
  {
    BOOST_CHECK_THROW(Rectangle(-40, 20, {100, 100}), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle(40, -20, {100, 100}), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle(-40, -20, {100,100}), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()
