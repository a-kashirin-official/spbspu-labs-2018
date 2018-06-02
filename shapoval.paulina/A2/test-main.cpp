#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>

#include "rectangle.hpp"
#include "circle.hpp"

const double EPSILON_TEST = 0.00001;

BOOST_AUTO_TEST_SUITE(CircleTests)

  BOOST_AUTO_TEST_CASE(MoveToXYTests)
  {
    shapoval::Circle new_circle({0,0},10);
    new_circle.move(10, 20);
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getFrameRect().pos.x, 10, EPSILON_TEST); 
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getFrameRect().pos.y, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getFrameRect().height / 2 , 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getArea(), 10 * 10 * M_PI, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointTests)
  {
    shapoval::Circle new_circle({0,0},10);
    new_circle.move({20, 10});
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getFrameRect().pos.x, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getFrameRect().pos.y, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getFrameRect().height / 2 , 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getArea(), 10 * 10 * M_PI, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaScaleTest)
  {
    shapoval::Circle new_circle({0,0},10);
    new_circle.scale(5);
    BOOST_CHECK_CLOSE_FRACTION(new_circle.getArea(), 10 * 10 * M_PI * 5 * 5, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(InvalidCircleTest)
  {
    BOOST_CHECK_THROW(shapoval::Circle({0,0},-10), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidCircleScaleTest)
  {
    shapoval::Circle new_circle ({0,0},10);
    BOOST_CHECK_THROW(new_circle.scale(-5), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleTests)

  BOOST_AUTO_TEST_CASE(MoveToXYTests)
  {
    shapoval::Rectangle new_rectangle({0,0}, 10, 20);
    new_rectangle.move(10, 20);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getFrameRect().pos.x, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getFrameRect().pos.y, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getFrameRect().height , 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getFrameRect().width , 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getArea(), 10 * 20 , EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointTests)
  {
    shapoval::Rectangle new_rectangle({0,0}, 10, 20);
    new_rectangle.move({20, 10});
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getFrameRect().pos.x, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getFrameRect().pos.y, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getFrameRect().height , 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getFrameRect().width , 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getArea(), 10 * 20 , EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaScaleTest)
  {
    shapoval::Rectangle new_rectangle({0,0}, 10, 20);
    new_rectangle.scale(5);
    BOOST_CHECK_CLOSE_FRACTION(new_rectangle.getArea(), 10 * 5 * 20 * 5 , EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(InvalidRectangleHeightTest)
  {
    BOOST_CHECK_THROW(shapoval::Rectangle({0,0}, -10, 20), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidRectangleWigthTest)
  {
    BOOST_CHECK_THROW(shapoval::Rectangle({0,0}, 10, -20), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidRectangleScaleTest)
  {
    shapoval::Rectangle new_rectangle ({0,0}, 10, 20);
    BOOST_CHECK_THROW(new_rectangle.scale(-5), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
