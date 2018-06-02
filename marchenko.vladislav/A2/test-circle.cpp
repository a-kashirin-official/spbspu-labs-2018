#include <boost/test/unit_test.hpp>
#include "circle.hpp"

const double epsilon = 0.00001;

BOOST_AUTO_TEST_SUITE(testsOfCircle)

BOOST_AUTO_TEST_CASE(moveToNewPosition)
{
  marchenko::Circle testCircle({13.0, 13.5}, 37.0);
  double heightOfFrRectBeforeMoving = testCircle.getFrameRect().height;
  double weightOfFrRectBeforeMoving = testCircle.getFrameRect().width;
  double areaBeforeMoving = testCircle.getArea();
  testCircle.move({33.0, 24.0});
  BOOST_CHECK_EQUAL(heightOfFrRectBeforeMoving, testCircle.getFrameRect().height);
  BOOST_CHECK_EQUAL(weightOfFrRectBeforeMoving, testCircle.getFrameRect().width);
  BOOST_CHECK_EQUAL(areaBeforeMoving, testCircle.getArea());
  BOOST_CHECK_EQUAL(33.0, testCircle.getFrameRect().pos.x);
  BOOST_CHECK_EQUAL(24.0, testCircle.getFrameRect().pos.y);
}

BOOST_AUTO_TEST_CASE(moveByDxAndDy)
{
  marchenko::Circle testCircle({13.0, 13.7}, 49.0);
  double heightOfFrRectBeforeMoving = testCircle.getFrameRect().height;
  double weightOfFrRectBeforeMoving = testCircle.getFrameRect().width;
  double areaBeforeMoving = testCircle.getArea();
  double xBeforeMoving = testCircle.getFrameRect().pos.x;
  double yBeforeMoving = testCircle.getFrameRect().pos.y;
  testCircle.move(500.0, 500.0);
  BOOST_CHECK_EQUAL(heightOfFrRectBeforeMoving, testCircle.getFrameRect().height);
  BOOST_CHECK_EQUAL(weightOfFrRectBeforeMoving, testCircle.getFrameRect().width);
  BOOST_CHECK_EQUAL(areaBeforeMoving, testCircle.getArea());
  BOOST_CHECK_CLOSE(xBeforeMoving + 500.0, testCircle.getFrameRect().pos.x, epsilon);
  BOOST_CHECK_CLOSE(yBeforeMoving + 500.0, testCircle.getFrameRect().pos.y, epsilon);
}

BOOST_AUTO_TEST_CASE(scaling)
{
  marchenko::Circle testCircle({173.82, 163.43}, 8.99);
  double xBeforeScaling = testCircle.getFrameRect().pos.x;
  double yBeforeScaling = testCircle.getFrameRect().pos.y;
  double areaBeforeScaling = testCircle.getArea();
  testCircle.scale(5.0);
  BOOST_CHECK_EQUAL(xBeforeScaling, testCircle.getFrameRect().pos.x);
  BOOST_CHECK_EQUAL(yBeforeScaling, testCircle.getFrameRect().pos.y);
  BOOST_CHECK_CLOSE(areaBeforeScaling * 25.0, testCircle.getArea(), epsilon);
}

BOOST_AUTO_TEST_CASE(invalidArguments)
{
  BOOST_CHECK_THROW(marchenko::Circle({12.0,12.0}, -78.5), std::invalid_argument);
  marchenko::Circle testCircle({173.82, 163.43}, 8.99);
  BOOST_CHECK_THROW(testCircle.scale(-67.0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
