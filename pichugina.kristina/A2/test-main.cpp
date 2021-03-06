#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>

#include "rectangle.hpp"
#include "circle.hpp"

const double EPSILON_TEST = 0.00001;

BOOST_AUTO_TEST_SUITE(CircleTests)
  
  BOOST_AUTO_TEST_CASE(MoveByDeltaTest)
  {
    pichugina::Circle circle{ { 15.32, 1.23 }, 4.3 };
    circle.move( 5.27, 18.9 );
    BOOST_CHECK_CLOSE_FRACTION(circle.getFrameRect().height / 2, 4.3, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), 4.3 * 4.3 * M_PI, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(MoveToPosTest)
  {
    pichugina::Circle circle{ { 15.32, 1.23 }, 4.3 };
    circle.move( { 5.27, 18.9 } );
    BOOST_CHECK_CLOSE_FRACTION(circle.getFrameRect().height / 2, 4.3, EPSILON_TEST); 
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), 4.3 * 4.3 * M_PI, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaScaleTest)
  {
    pichugina::Circle circle{ { 15.32, 1.23 }, 4.3 };
    circle.scale(5);
    BOOST_CHECK_CLOSE_FRACTION(circle.getArea(), 4.3 * 4.3 * M_PI * 5 * 5, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentInCircleConstructorTest)
  {
    BOOST_CHECK_THROW(pichugina::Circle( { 15.32, 1.23 }, -1 ), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentInCircleScaleTest)
  {
    pichugina::Circle circle{ { 15.32, 1.23 }, 4.3 };
    BOOST_CHECK_THROW(circle.scale(-1), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleTests)
  
  BOOST_AUTO_TEST_CASE(MoveByDeltaTest)
  {
    pichugina::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 10.79 };
    rectangle.move( 5.27, 18.9 );
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getFrameRect().height, 10.79, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getFrameRect().width, 7.0, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(), 7.0 * 10.79, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(MoveToPosTest)
  {
    pichugina::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 10.79 };
    rectangle.move( { 5.27, 18.9 } );
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getFrameRect().height, 10.79, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getFrameRect().width, 7.0, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(), 7.0 * 10.79, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaScaleTest)
  {
    pichugina::Rectangle rectangle{ { 19.64, 8.35 }, 7.0, 10.79 };
    rectangle.scale(5);
    BOOST_CHECK_CLOSE_FRACTION(rectangle.getArea(), 7.0 * 10.79 * 5 * 5, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentInRectangleConstructorTest)
  {
    BOOST_CHECK_THROW(pichugina::Rectangle( { 15.32, 16.23 }, -3.26, 7.15 ), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidArgumentInRectangleScaleTest)
  {
    pichugina::Rectangle rectangle{ { 15.32, 16.23 }, 6.21, 8.0 };
    BOOST_CHECK_THROW(rectangle.scale(-1.0), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()
