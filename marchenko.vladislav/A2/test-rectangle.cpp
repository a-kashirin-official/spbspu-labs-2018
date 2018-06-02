#include <boost/test/unit_test.hpp>
#include "rectangle.hpp"

const double epsilon = 0.00001;

BOOST_AUTO_TEST_SUITE(testsOfRectangle)

BOOST_AUTO_TEST_CASE(moveToNewPosition)
{
  marchenko::Rectangle testRectangle(35.0, 43.0, {34.0, 98.76});
  double heightOfFrRectBeforeMoving = testRectangle.getFrameRect().height;
  double weightOfFrRectBeforeMoving = testRectangle.getFrameRect().width;
  double areaBeforeMoving = testRectangle.getArea();
  testRectangle.move({33.0, 24.0});
  BOOST_CHECK_EQUAL(heightOfFrRectBeforeMoving, testRectangle.getFrameRect().height);
  BOOST_CHECK_EQUAL(weightOfFrRectBeforeMoving, testRectangle.getFrameRect().width);
  BOOST_CHECK_EQUAL(areaBeforeMoving, testRectangle.getArea());
  BOOST_CHECK_EQUAL(33.0, testRectangle.getFrameRect().pos.x);
  BOOST_CHECK_EQUAL(24.0, testRectangle.getFrameRect().pos.y);
}

BOOST_AUTO_TEST_CASE(moveByDxAndDy)
{
  marchenko::Rectangle testRectangle(35.0, 43.0, {34.0, 98.76});
  double heightOfFrRectBeforeMoving = testRectangle.getFrameRect().height;
  double weightOfFrRectBeforeMoving = testRectangle.getFrameRect().width;
  double areaBeforeMoving = testRectangle.getArea();
  double xBeforeMoving = testRectangle.getFrameRect().pos.x;
  double yBeforeMoving = testRectangle.getFrameRect().pos.y;
  testRectangle.move(500.0, 500.0);
  BOOST_CHECK_EQUAL(heightOfFrRectBeforeMoving, testRectangle.getFrameRect().height);
  BOOST_CHECK_EQUAL(weightOfFrRectBeforeMoving, testRectangle.getFrameRect().width);
  BOOST_CHECK_EQUAL(areaBeforeMoving, testRectangle.getArea());
  BOOST_CHECK_CLOSE(xBeforeMoving + 500.0, testRectangle.getFrameRect().pos.x, epsilon);
  BOOST_CHECK_CLOSE(yBeforeMoving + 500.0, testRectangle.getFrameRect().pos.y, epsilon);
}

BOOST_AUTO_TEST_CASE(scaling)
{
  marchenko::Rectangle testRectangle(35.0, 43.0, {34.0, 98.76});
  double xBeforeScaling = testRectangle.getFrameRect().pos.x;
  double yBeforeScaling = testRectangle.getFrameRect().pos.y;
  double areaBeforeScaling = testRectangle.getArea();
  testRectangle.scale(5.0);
  BOOST_CHECK_EQUAL(xBeforeScaling, testRectangle.getFrameRect().pos.x);
  BOOST_CHECK_EQUAL(yBeforeScaling, testRectangle.getFrameRect().pos.y);
  BOOST_CHECK_CLOSE(areaBeforeScaling * 25.0, testRectangle.getArea(), epsilon);
}

BOOST_AUTO_TEST_CASE(invalidArguments)
{
  BOOST_CHECK_THROW(marchenko::Rectangle(-35.0, -43.0, {34.0, 98.76}), std::invalid_argument);
  marchenko::Rectangle testRectangle(35.0, 43.0, {34.0, 98.76});
  BOOST_CHECK_THROW(testRectangle.scale(-67.0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
