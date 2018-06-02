#define BOOST_TEST_MODULE

#include <cmath>
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"

const double EPSILON = 0.001;

BOOST_AUTO_TEST_SUITE(Rectangle_Tests)

  BOOST_AUTO_TEST_CASE(Constructor_Test)
  {
    BOOST_CHECK_THROW(almukhametov::Rectangle rectangle(-2.0, -4.0, {0.0, 0.0}), std::invalid_argument);
    BOOST_CHECK_THROW(almukhametov::Rectangle rectangle(-2.0, 4.0, {0.0, 0.0}), std::invalid_argument);
    BOOST_CHECK_THROW(almukhametov::Rectangle rectangle(2.0, -4.0, {0.0, 0.0}), std::invalid_argument)
  }

  BOOST_AUTO_TEST_CASE(MovingToPos)
  {
    almukhametov::Rectangle rectangle(7.0, 6.0, {0.0, 1.0});
    rectangle.move({4.0, 0.0});
    BOOST_CHECK_CLOSE(7.0, rectangle.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(6.0, rectangle.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, 4.0, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, 0.0, EPSILON);
    BOOST_CHECK_CLOSE(7.0*6.0, rectangle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Moving)
  {
    almukhametov::Rectangle rectangle(7.0, 6.0, {3.0, 1.0});
    rectangle.move(4.0, 0.0);
    BOOST_CHECK_CLOSE(7.0, rectangle.getFrameRect().height, EPSILON);
    BOOST_CHECK_CLOSE(6.0, rectangle.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, 7.0, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, 1.0, EPSILON);
    BOOST_CHECK_CLOSE(7.0*6.0, rectangle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    almukhametov::Rectangle rectangle(7.0, 6.0, {0.0, 1.0});
    rectangle.scale(4.0);
    BOOST_CHECK_CLOSE(7.0*6.0*4.0*4.0, rectangle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Scaling_InvalidParameters)
  {
    almukhametov::Rectangle rectangle(7.0, 6.0, {0.0, 1.0});
    BOOST_CHECK_THROW(rectangle.scale(-1.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Circle_Tests)

  BOOST_AUTO_TEST_CASE(Constructor_Test)
  {
    BOOST_CHECK_THROW(almukhametov::Circle circle(-6.0, {4.0, 7.0}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MovingToPos)
  {
    almukhametov::Circle circle(2.0, {3.0, 1.0});
    circle.move({2.0, 7.0});
    BOOST_CHECK_CLOSE(2.0, circle.getFrameRect().height/2, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, 2.0, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, 7.0, EPSILON);
    BOOST_CHECK_CLOSE(2.0*2.0*M_PI, circle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Moving)
  {
    almukhametov::Circle circle(2.0, {3.0, 1.0});
    circle.move(2.0, 7.0);
    BOOST_CHECK_CLOSE(2.0, circle.getFrameRect().height/2, EPSILON);
    BOOST_CHECK_CLOSE(5.0, circle.getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(8.0, circle.getFrameRect().pos.y, EPSILON);
    BOOST_CHECK_CLOSE(2.0*2.0*M_PI, circle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    almukhametov::Circle circle(2.0, {3.0, 1.0});
    circle.scale(3.5);
    BOOST_CHECK_CLOSE(2.0*2.0*3.5*3.5*M_PI, circle.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(Scaling_InvalidParameters)
  {
    almukhametov::Circle circle(2.0, {3.0, 1.0});
    BOOST_CHECK_THROW(circle.scale(-8.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
