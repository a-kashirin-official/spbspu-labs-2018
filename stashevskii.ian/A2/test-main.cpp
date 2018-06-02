#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>

#include "rectangle.hpp"
#include "circle.hpp"

const double EPSILON_TEST=0.00001;


BOOST_AUTO_TEST_SUITE(CircleTests)

  BOOST_AUTO_TEST_CASE(MoveToXYRadiusTest)
  {
    stashevskii::Circle new_circle(10, {0,0});
    new_circle.move(10, 20);
    BOOST_CHECK_CLOSE_FRACTION (new_circle.getFrameRect().height / 2 , 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_circle.getArea(), 10 * 10 * M_PI, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_circle.getPosition().x, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_circle.getPosition().y, 20, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointRadiusTest)
  {
    stashevskii::Circle new_circle(10, {0,0});
    new_circle.move({20, 10});
    BOOST_CHECK_CLOSE_FRACTION (new_circle.getFrameRect().height / 2 , 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_circle.getArea(), 10 * 10 * M_PI, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_circle.getPosition().x, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_circle.getPosition().y, 10, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(MoveToXYAreaTest)
  {
    stashevskii::Circle new_circle(10, {0,0});
    new_circle.move(10, 20);
    BOOST_CHECK_CLOSE_FRACTION (new_circle.getArea(), 10 * 10 * M_PI, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_circle.getPosition().x, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_circle.getPosition().y, 20, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointAreaTest)
  {
    stashevskii::Circle new_circle(10, {0,0});
    new_circle.move({20,10});
    BOOST_CHECK_CLOSE_FRACTION (new_circle.getArea(), 10 * 10 * M_PI, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_circle.getPosition().x, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_circle.getPosition().y, 10, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaScaleTest)
  {
    stashevskii::Circle new_circle(10, {0,0});
    new_circle.scale(5);
    BOOST_CHECK_CLOSE_FRACTION (new_circle.getArea(), 10 * 10 * M_PI * 5 * 5, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(InvalidCircleTest)
  {
    BOOST_CHECK_THROW (stashevskii::Circle(-5.5, {0,0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidCircleScaleTest)
  {
    stashevskii::Circle new_circle (10, {0,0});
    BOOST_CHECK_THROW (new_circle.scale(-5), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleTests)

  BOOST_AUTO_TEST_CASE(MoveToXYHeightTest)
  {
    stashevskii::Rectangle new_rectangle(10, 20, {0,0});
    new_rectangle.move(10, 20);
    BOOST_CHECK_CLOSE_FRACTION (new_rectangle.getFrameRect().height , 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_rectangle.getPosition().x, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_rectangle.getPosition().y, 20, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointHeightTest)
  {
    stashevskii::Rectangle new_rectangle(10, 20, {0,0});
    new_rectangle.move({20, 10});
    BOOST_CHECK_CLOSE_FRACTION (new_rectangle.getFrameRect().height , 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_rectangle.getPosition().x, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_rectangle.getPosition().y, 10, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(MoveToXYWidthTest)
  {
    stashevskii::Rectangle new_rectangle(10, 20, {0,0});
    new_rectangle.move(10, 20);
    BOOST_CHECK_CLOSE_FRACTION (new_rectangle.getFrameRect().width , 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_rectangle.getPosition().x, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_rectangle.getPosition().y, 20, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointWidthTest)
  {
    stashevskii::Rectangle new_rectangle(10, 20, {0,0});
    new_rectangle.move({20, 10});
    BOOST_CHECK_CLOSE_FRACTION (new_rectangle.getFrameRect().width , 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_rectangle.getPosition().x, 20, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_rectangle.getPosition().y, 10, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(MoveToXYAreaTest)
  {
    stashevskii::Rectangle new_rectangle(10, 20, {0,0});
    new_rectangle.move(10, 20);
    BOOST_CHECK_CLOSE_FRACTION (new_rectangle.getArea(), 10 * 20 , EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_rectangle.getPosition().x, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_rectangle.getPosition().y, 20, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointAreaTest)
  {
    stashevskii::Rectangle new_rectangle(10, 20, {0,0});
    new_rectangle.move({10,20});
    BOOST_CHECK_CLOSE_FRACTION (new_rectangle.getArea(), 10 * 20 , EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_rectangle.getPosition().x, 10, EPSILON_TEST);
    BOOST_CHECK_CLOSE_FRACTION (new_rectangle.getPosition().y, 20, EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaScaleTest)
  {
    stashevskii::Rectangle new_rectangle(10, 20, {0,0});
    new_rectangle.scale(5);
    BOOST_CHECK_CLOSE_FRACTION (new_rectangle.getArea(), 10 * 5 * 20 * 5 , EPSILON_TEST);
  }

  BOOST_AUTO_TEST_CASE(InvalidRectangleHeightTest)
  {
    BOOST_CHECK_THROW (stashevskii::Rectangle(10, -5.5, {0,0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidRectangleWigthTest)
  {
    BOOST_CHECK_THROW (stashevskii::Rectangle(-5.5, 10, {0,0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidRectangleScaleTest)
  {
    stashevskii::Rectangle new_rectangle (10, 20, {0,0});
    BOOST_CHECK_THROW (new_rectangle.scale(-5), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
