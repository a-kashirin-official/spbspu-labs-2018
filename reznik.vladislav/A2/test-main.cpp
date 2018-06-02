#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include <stdexcept>
#include <cmath>

#include "rectangle.hpp"
#include "circle.hpp"

const double EPSILON = 0.000001;

BOOST_AUTO_TEST_SUITE(CircleTests)

  BOOST_AUTO_TEST_CASE(AbsoluteMoveTests)
  {
    reznik::Circle circ(5,{0,0});
    circ.move(15,20);
    BOOST_CHECK_CLOSE_FRACTION(circ.getFrameRect().pos.x, 15, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(circ.getFrameRect().pos.y, 20, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(circ.getFrameRect().height / 2 , 5, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(circ.getArea(), 5 * 5 * M_PI, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointTests)
  {
    reznik::Circle circ(3,{5,5});
    circ.move({10,15});
    BOOST_CHECK_CLOSE_FRACTION(circ.getFrameRect().pos.x, 10, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(circ.getFrameRect().pos.y, 15, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(circ.getFrameRect().height / 2 , 3, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(circ.getArea(), 3 * 3 * M_PI, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaScaleTest)
  {
    reznik::Circle circ(3,{5,5});
    circ.scale(5);
    BOOST_CHECK_CLOSE_FRACTION(circ.getArea(), 3 * 3 * M_PI * 5 * 5, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidCircleTest)
  {
    BOOST_CHECK_THROW(reznik::Circle(-10,{0,0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidCircleScaleTest)
  {
    reznik::Circle circ(3,{5,5});
    BOOST_CHECK_THROW(circ.scale(-5), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(RectangleTests)

  BOOST_AUTO_TEST_CASE(AbsoluteMoveTests)
  {
    reznik::Rectangle rect(10,2,{10,15});
    rect.move(10, 20);
    BOOST_CHECK_CLOSE_FRACTION(rect.getFrameRect().pos.x, 20, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(rect.getFrameRect().pos.y, 35, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(rect.getFrameRect().height , 2, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(rect.getFrameRect().width , 10, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(rect.getArea(), 10 * 2 , EPSILON);
  }

  BOOST_AUTO_TEST_CASE(MoveToPointTests)
  {
    reznik::Rectangle rect(10,2,{10,15});
    rect.move({20, 10});
    BOOST_CHECK_CLOSE_FRACTION(rect.getFrameRect().pos.x, 20, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(rect.getFrameRect().pos.y, 10, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(rect.getFrameRect().height , 2, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(rect.getFrameRect().width , 10, EPSILON);
    BOOST_CHECK_CLOSE_FRACTION(rect.getArea(), 10 * 2 , EPSILON);
  }

  BOOST_AUTO_TEST_CASE(ChangeAreaScaleTest)
  {
    reznik::Rectangle rect(10,2,{10,15});
    rect.scale(5);
    BOOST_CHECK_CLOSE_FRACTION(rect.getArea(), 10 * 2 * 5 * 5 , EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidRectangleWigthTest)
  {
    BOOST_CHECK_THROW(reznik::Rectangle(-10,2,{10,15}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidRectangleHeightTest)
  {
    BOOST_CHECK_THROW(reznik::Rectangle(10,-2,{10,15}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidRectangleScaleTest)
  {
    reznik::Rectangle rect(10,2,{10,15});
    BOOST_CHECK_THROW(rect.scale(-5), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
