#define BOOST_TEST_MODULE Test

#include "rectangle.hpp"
#include "circle.hpp"
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>

#define EPSILON 1E-5

using namespace solovev;

BOOST_AUTO_TEST_SUITE(TestRect)
  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Rectangle rect = Rectangle({5,5}, 5, 5);

    double areaBeforeMove = rect.getArea();
    double widthBeforeMove = rect.getFrameRect().width;
    double heightBeforeMove = rect.getFrameRect().height;

    rect.move({2,4});

    BOOST_CHECK_EQUAL(areaBeforeMove, rect.getArea());
    BOOST_CHECK_EQUAL(widthBeforeMove, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(heightBeforeMove, rect.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(RelativeMove)
  {
    Rectangle rect = Rectangle({5,5}, 5, 5);

    double areaBeforeMove = rect.getArea();
    double widthBeforeMove = rect.getFrameRect().width;
    double heightBeforeMove = rect.getFrameRect().height;

    rect.move(10, -10);

    BOOST_CHECK_EQUAL(areaBeforeMove, rect.getArea());
    BOOST_CHECK_EQUAL(widthBeforeMove, rect.getFrameRect().width);
    BOOST_CHECK_EQUAL(heightBeforeMove, rect.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    Rectangle rect = Rectangle ({5,5}, 5, 5);
    double areaBeforeScaling = rect.getArea();

    double factor = 5.2;

    rect.scale(factor);
    BOOST_CHECK_CLOSE(factor * factor, rect.getArea()/areaBeforeScaling, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidParametrsForConstructor)
  {
    BOOST_CHECK_THROW(Rectangle({5, 5}, -5, -5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidParametrForScale)
  {
    Rectangle rect = Rectangle ({5,5}, 5, 5);
    BOOST_CHECK_THROW (rect.scale(-1.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(TestCirc)
  BOOST_AUTO_TEST_CASE(MoveToPoint)
  {
    Circle circ = Circle (5, {5,5});

    double areaBeforeMove = circ.getArea();
    double widthBeforeMove = circ.getFrameRect().width;
    double heightBeforeMove = circ.getFrameRect().height;

    circ.move({2,4});

    BOOST_CHECK_EQUAL(areaBeforeMove, circ.getArea());
    BOOST_CHECK_EQUAL(widthBeforeMove, circ.getFrameRect().width);
    BOOST_CHECK_EQUAL(heightBeforeMove, circ.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(RelativeMove)
  {
    Circle circ = Circle (5, {5,5});

    double areaBeforeMove = circ.getArea();
    double widthBeforeMove = circ.getFrameRect().width;
    double heightBeforeMove = circ.getFrameRect().height;

    circ.move(23,-14);

    BOOST_CHECK_EQUAL(areaBeforeMove, circ.getArea());
    BOOST_CHECK_EQUAL(widthBeforeMove, circ.getFrameRect().width);
    BOOST_CHECK_EQUAL(heightBeforeMove, circ.getFrameRect().height);
  }

  BOOST_AUTO_TEST_CASE(Scale)
  {
    Circle circ = Circle(5, {5,5});
    double areaBeforeScaling = circ.getArea();

    double factor = 44.4;

    circ.scale(factor);
    BOOST_CHECK_CLOSE(factor*factor, circ.getArea()/areaBeforeScaling, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(InvalidParametrsForConstructor)
  {
    BOOST_CHECK_THROW(Circle(-12.0,{5,5}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(InvalidParameterForScale)
  {
    Circle circ = Circle (5, {5.0, 5.0});
    BOOST_CHECK_THROW(circ.scale(-1.0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()
