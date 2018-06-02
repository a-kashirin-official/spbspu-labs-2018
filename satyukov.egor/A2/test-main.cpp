#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>  
#include <stdexcept>
#include <cmath>

#include "circle.hpp"
#include "rectangle.hpp"

#define EPSILON 1e-7

BOOST_AUTO_TEST_SUITE(CircleTests)

  BOOST_AUTO_TEST_CASE(ConstantRadiusMoveToPointTest)
  {
    satyukov::Circle testCircle ({ 5.0, 0.5 }, 13.33);
    testCircle.move({ 5.5, 5.5 });
    BOOST_REQUIRE_EQUAL(testCircle.getRadius(), 13.33);
  }

  BOOST_AUTO_TEST_CASE(ConstantRadiusMoveByDeltaTest)
  {
    satyukov::Circle testCircle ({ 5.0, 0.5 }, 13.33);
    testCircle.move(0.5, 5.0);
    BOOST_REQUIRE_EQUAL(testCircle.getRadius(), 13.33);
  }

  BOOST_AUTO_TEST_CASE(ConstantAreaMoveToPointTest)
  {
    satyukov::Circle testCircle ({ 5.0, 0.5 }, 13.33);
    testCircle.move({ 5.5, 5.5 });
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getArea(), M_PI * 13.33 * 13.33, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ConstantAreaMoveByDeltaTest)
  {
    satyukov::Circle testCircle ({ 5.0, 0.5 }, 13.33);
    testCircle.move(0.5, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getArea(), M_PI * 13.33 * 13.33, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaByScaleTest)
  {
    satyukov::Circle testCircle ({ 5.0, 0.5 }, 13.33);
    testCircle.scale(5);
    BOOST_CHECK_CLOSE_FRACTION(testCircle.getArea(), M_PI * 13.33 * 5 * 13.33 * 5, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentRadiusTest)
  {
    BOOST_CHECK_THROW(satyukov::Circle testCircle ({ 5.0, 0.5 }, -13.33), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentScaleCoefficientTest)
  {
    satyukov::Circle testCircle ({ 5.0, 0.5 }, 13.33);
    BOOST_CHECK_THROW(testCircle.scale(-1), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleTests)

  BOOST_AUTO_TEST_CASE(ConstantWidthMoveToPointTest)
  {
    satyukov::Rectangle testRectangle ({ 5.0, 0.5 }, 3.33, 10.0);
    testRectangle.move({ 5.5, 5.5 });
    BOOST_REQUIRE_EQUAL(testRectangle.getWidth(), 3.33);
  }

  BOOST_AUTO_TEST_CASE(ConstantHeightMoveToPointTest)
  {
    satyukov::Rectangle testRectangle ({ 5.0, 0.5 }, 3.33, 10.0);
    testRectangle.move({ 5.5, 5.5 });
    BOOST_REQUIRE_EQUAL(testRectangle.getHeight(), 10.0);
  }

  BOOST_AUTO_TEST_CASE(ConstantWidthMoveByDeltaTest)
  {
    satyukov::Rectangle testRectangle ({ 5.0, 0.5 }, 3.33, 10.0);
    testRectangle.move(0.5, 5.0);
    BOOST_REQUIRE_EQUAL(testRectangle.getWidth(), 3.33);
  }

  BOOST_AUTO_TEST_CASE(ConstantHeightMoveByDeltaTest)
  {
    satyukov::Rectangle testRectangle ({ 5.0, 0.5 }, 3.33, 10.0);
    testRectangle.move(0.5, 5.0);
    BOOST_REQUIRE_EQUAL(testRectangle.getHeight(), 10.0);
  }

  BOOST_AUTO_TEST_CASE(ConstantAreaMoveToPointTest)
  {
    satyukov::Rectangle testRectangle ({ 5.0, 0.5 }, 3.33, 10.0);
    testRectangle.move({ 5.5, 5.5 });
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getArea(), 3.33 * 10.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ConstantAreaMoveByDeltaTest)
  {
    satyukov::Rectangle testRectangle ({ 5.0, 0.5 }, 3.33, 10.0);
    testRectangle.move(0.5, 5.0);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getArea(), 3.33 * 10.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaByScaleTest)
  {
    satyukov::Rectangle testRectangle ({ 5.0, 0.5 }, 3.33, 10.0);
    testRectangle.scale(20);
    BOOST_CHECK_CLOSE_FRACTION(testRectangle.getArea(), 3.33 * 20 * 10.0 * 20, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentWidthTest)
  {
    BOOST_CHECK_THROW(satyukov::Rectangle testRectangle ({ 5.0, 0.5 }, -3.33, 10.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentHeightTest)
  {
    BOOST_CHECK_THROW(satyukov::Rectangle testRectangle ({ 5.0, 0.5 }, 3.33, -10.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentScaleCoefficientTest)
  {
    satyukov::Rectangle testRectangle ({ 5.0, 0.5 }, 3.33, 10.0);
    BOOST_CHECK_THROW(testRectangle.scale(-1), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
