#define BOOST_TEST_MODULE Main
#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"

using namespace shumkovskaya;

const double DELTA  = 0.00001;
// tests for rectangle
BOOST_AUTO_TEST_SUITE(TestsForRectangle)

  BOOST_AUTO_TEST_CASE(TestIncorrectParameters)
  {
    BOOST_CHECK_THROW(Rectangle rect(-15, 4,  {2, 1}), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle rect(15, -4,  {2, 1}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestScaling)
  {
    Rectangle rect(5, 4,  {3, 2});
    double areaBeforeScaling = rect.getArea();
    rectangle_t frameRectBefore = rect.getFrameRect();
    rect.scale(2.1);
    BOOST_CHECK_CLOSE(areaBeforeScaling * 4.41, rect.getArea(), DELTA);
    BOOST_CHECK_CLOSE(2.1 * frameRectBefore.width, rect.getFrameRect().width, DELTA);
    BOOST_CHECK_CLOSE(2.1 * frameRectBefore.height, rect.getFrameRect().height, DELTA);
    BOOST_CHECK_THROW(rect.scale(-15), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestMoving)
  {
    Rectangle rect(2, 10, {-9, 4});
    double areaBeforeMoving = rect.getArea();
    rectangle_t frameRectBefore = rect.getFrameRect();
    rect.move({3.3, 3.9});
    BOOST_CHECK_EQUAL(rect.getArea(), areaBeforeMoving);
    BOOST_CHECK_EQUAL(frameRectBefore.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(frameRectBefore.height, rect.getFrameRect().height);
    rect.move(5.8, 9.0);
    BOOST_CHECK_EQUAL(rect.getArea(), areaBeforeMoving);
    BOOST_CHECK_EQUAL(frameRectBefore.width, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(frameRectBefore.height, rect.getFrameRect().height);
  }

BOOST_AUTO_TEST_SUITE_END()

//tests for circle
BOOST_AUTO_TEST_SUITE(TestsForCirle)

  BOOST_AUTO_TEST_CASE(TestIncorrectParameters)
  {
    BOOST_CHECK_THROW(Circle cir(-7,  {5, 3}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestScaling)
  {
    Circle cir(7, {5, 3});
    double areaBeforeScaling = cir.getArea();
    rectangle_t frameRectBefore = cir.getFrameRect();
    cir.scale(0.4);
    BOOST_CHECK_CLOSE(areaBeforeScaling * 0.16, cir.getArea(), DELTA);
    BOOST_CHECK_CLOSE(0.4 * frameRectBefore.width, cir.getFrameRect().width, DELTA);
    BOOST_CHECK_CLOSE(0.4 * frameRectBefore.height, cir.getFrameRect().height, DELTA);
    BOOST_CHECK_THROW(cir.scale(-7), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(TestMoving)
  {
    Circle cir(2, {-9, 4});
    double areaBeforeMoving = cir.getArea();
    rectangle_t frameRectBefore = cir.getFrameRect();
    cir.move({4.6, 6.9});
    BOOST_CHECK_EQUAL(cir.getArea(), areaBeforeMoving);
    BOOST_CHECK_EQUAL(frameRectBefore.width, cir.getFrameRect().width);
    BOOST_CHECK_EQUAL(frameRectBefore.height, cir.getFrameRect().height);
    cir.move(5.4, 9.2);
    BOOST_CHECK_EQUAL(cir.getArea(), areaBeforeMoving);
    BOOST_CHECK_EQUAL(frameRectBefore.width, cir.getFrameRect().width);
    BOOST_CHECK_EQUAL(frameRectBefore.height, cir.getFrameRect().height);
  }

BOOST_AUTO_TEST_SUITE_END()
