#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "circle.hpp"
#include "rectangle.hpp"

const double epsilon = 0.00001;

BOOST_AUTO_TEST_SUITE(testsForRectangle)
BOOST_AUTO_TEST_CASE(moveToPosition)
{
  kadyrov::Rectangle testRectangle({ 35.0, 40.0, { 30.0, 50.1 }});
  double originalHeight = testRectangle.getFrameRect().height;
  double originalWidth = testRectangle.getFrameRect().width;
  double originalArea = testRectangle.getArea();
  testRectangle.move({ 25.0, 30.0 });
  BOOST_CHECK_CLOSE(originalHeight, testRectangle.getFrameRect().height, epsilon);
  BOOST_CHECK_CLOSE(originalWidth, testRectangle.getFrameRect().width, epsilon);
  BOOST_CHECK_CLOSE(originalArea, testRectangle.getArea(), epsilon);
  BOOST_CHECK_CLOSE(25.0, testRectangle.getFrameRect().pos.x, epsilon);
  BOOST_CHECK_CLOSE(30.0, testRectangle.getFrameRect().pos.y, epsilon);
}

BOOST_AUTO_TEST_CASE(moveWithDxDy)
{
  kadyrov::Rectangle testRectangle({ 35.0, 40.0,{ 30.0, 50.1 } });
  double originalHeight = testRectangle.getFrameRect().height;
  double originalWidth= testRectangle.getFrameRect().width;
  double originalArea = testRectangle.getArea();
  double originalX = testRectangle.getFrameRect().pos.x;
  double originalY = testRectangle.getFrameRect().pos.y;
  testRectangle.move(25.0, 30.0);
  BOOST_CHECK_CLOSE(originalHeight, testRectangle.getFrameRect().height, epsilon);
  BOOST_CHECK_CLOSE(originalWidth, testRectangle.getFrameRect().width, epsilon);
  BOOST_CHECK_CLOSE(originalArea, testRectangle.getArea(), epsilon);
  BOOST_CHECK_CLOSE(originalX + 25.0, testRectangle.getFrameRect().pos.x, epsilon);
  BOOST_CHECK_CLOSE(originalY + 30.0, testRectangle.getFrameRect().pos.y, epsilon);
}

BOOST_AUTO_TEST_CASE(scaling)
{
  kadyrov::Rectangle testRectangle({ 35.0, 40.0,{ 30.0, 50.1 } });
  double originalX = testRectangle.getFrameRect().pos.x;
  double originalY = testRectangle.getFrameRect().pos.y;
  double originalArea = testRectangle.getArea();
  testRectangle.scale(5.0);
  BOOST_CHECK_CLOSE(originalX, testRectangle.getFrameRect().pos.x, epsilon);
  BOOST_CHECK_CLOSE(originalY, testRectangle.getFrameRect().pos.y, epsilon);
  BOOST_CHECK_CLOSE(originalArea * 25.0, testRectangle.getArea(), epsilon);
}

BOOST_AUTO_TEST_CASE(invalidArguments)
{
  BOOST_CHECK_THROW(kadyrov::Rectangle({ -35.0, -40.0,{ 30.0, 50.1 } }),   std::invalid_argument);
  kadyrov::Rectangle testRectangle({ 35.0, 40.0,{ 30.0, 50.1 } });
  BOOST_CHECK_THROW(testRectangle.scale(-2.0), std::invalid_argument);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(testsForCircle)
BOOST_AUTO_TEST_CASE(moveToPosition)
{
  kadyrov::Circle testCircle({ 30.0, 52.4 }, 14.0);
  double originalHeight = testCircle.getFrameRect().height;
  double originalWidth = testCircle.getFrameRect().width;
  double originalArea = testCircle.getArea();
  testCircle.move({ 20.0, 30.0 });
  BOOST_CHECK_CLOSE(originalHeight, testCircle.getFrameRect().height, epsilon);
  BOOST_CHECK_CLOSE(originalWidth, testCircle.getFrameRect().width, epsilon);
  BOOST_CHECK_CLOSE(originalArea, testCircle.getArea(), epsilon);
  BOOST_CHECK_CLOSE(20.0, testCircle.getFrameRect().pos.x, epsilon);
  BOOST_CHECK_CLOSE(30.0, testCircle.getFrameRect().pos.y, epsilon);
}

BOOST_AUTO_TEST_CASE(moveWithDxDy)

{
  kadyrov::Circle testCircle({ 30.0, 52.4 }, 14.0);
  double originalHeight = testCircle.getFrameRect().height;
  double originalWidth = testCircle.getFrameRect().width;
  double originalArea = testCircle.getArea();
  double originalX = testCircle.getFrameRect().pos.x;
  double originalY = testCircle.getFrameRect().pos.y;
  testCircle.move(100.0, 125.0);
  BOOST_CHECK_CLOSE(originalHeight, testCircle.getFrameRect().height, epsilon);
  BOOST_CHECK_CLOSE(originalWidth, testCircle.getFrameRect().width, epsilon);
  BOOST_CHECK_CLOSE(originalArea, testCircle.getArea(), epsilon);
  BOOST_CHECK_CLOSE(originalX + 100.0, testCircle.getFrameRect().pos.x, epsilon);
  BOOST_CHECK_CLOSE(originalY + 125.0, testCircle.getFrameRect().pos.y, epsilon);
}

BOOST_AUTO_TEST_CASE(scaling)
{
  kadyrov::Circle testCircle({ 30.0, 52.4 }, 14.0);
  double originalX = testCircle.getFrameRect().pos.x;
  double originalY = testCircle.getFrameRect().pos.y;
  double originalArea = testCircle.getArea();
  testCircle.scale(5.0);
  BOOST_CHECK_CLOSE(originalX, testCircle.getFrameRect().pos.x, epsilon);
  BOOST_CHECK_CLOSE(originalY, testCircle.getFrameRect().pos.y, epsilon);
  BOOST_CHECK_CLOSE(originalArea * 25.0, testCircle.getArea(), epsilon);
}

BOOST_AUTO_TEST_CASE(invalidArguments)
{
  BOOST_CHECK_THROW(kadyrov::Circle({ 1.0,1.0 }, -34.5), std::invalid_argument);
  kadyrov::Circle testCircle({ 25.1, 25.1 }, 6.0);
  BOOST_CHECK_THROW(testCircle.scale(-2.0), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
