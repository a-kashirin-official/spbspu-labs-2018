#define BOOST_TEST_MODULE MAIN
#include <stdexcept>
#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
using namespace gremiachenskii;
using namespace std;

const double EPSILON = 1E-1;

BOOST_AUTO_TEST_SUITE(RectangleTest)
  BOOST_AUTO_TEST_CASE(Constructing)
  {
    BOOST_CHECK_THROW(Rectangle({10.0, 10.0}, -10.0, -5.0), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle({20.0, 20.0}, -10.0, 5.0), std::invalid_argument);
    BOOST_CHECK_THROW(Rectangle({30.0, 30.0}, 5.0, -100.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MovingToPoint)
  {
    Rectangle rect({10.0, 10.0}, 10.0, 10.0);
    rectangle_t rectBeforeMoving = rect.getFrameRect();
    double areaBeforeMoving = rect.getArea();

    rect.move( {15.0, 15.0} );
    BOOST_CHECK_EQUAL(rect.getArea(), areaBeforeMoving);
    BOOST_CHECK_EQUAL(rect.getFrameRect().width, rectBeforeMoving.width);
    BOOST_CHECK_EQUAL(rect.getFrameRect().height, rectBeforeMoving.height);
  }

  BOOST_AUTO_TEST_CASE(RelativeMoving)
  {
    Rectangle rect({10.0, 10.0}, 10.0, 10.0);
    rectangle_t rectBeforeMoving = rect.getFrameRect();
    double areaBeforeMoving = rect.getArea();

    rect.move(10.0, 15.0);
    BOOST_CHECK_EQUAL(rect.getArea(), areaBeforeMoving);
    BOOST_CHECK_EQUAL(rect.getFrameRect().width, rectBeforeMoving.width);
    BOOST_CHECK_EQUAL(rect.getFrameRect().height, rectBeforeMoving.height);
  }

  BOOST_AUTO_TEST_CASE(InvalidScalingParameter)
  {
    Rectangle rect({10.0, 10.0}, 10.0, 10.0);
    BOOST_CHECK_THROW(rect.scale(-10.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    Rectangle rect({10.0, 10.0}, 10.0, 10.0);
    rectangle_t rectBeforeScaling = rect.getFrameRect();
    double areaBeforeScaling = rect.getArea();
    rect.scale(10.0);

    BOOST_CHECK_EQUAL(rect.getFrameRect().pos.x, rectBeforeScaling.pos.x);
    BOOST_CHECK_EQUAL(rect.getFrameRect().pos.y, rectBeforeScaling.pos.y);

    BOOST_CHECK_CLOSE(rect.getFrameRect().width, rectBeforeScaling.width * 10.0, EPSILON);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height, rectBeforeScaling.height * 10.0, EPSILON);

    BOOST_CHECK_CLOSE(rect.getArea(), areaBeforeScaling * 10.0 * 10.0, EPSILON);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CircleTest)
  BOOST_AUTO_TEST_CASE(Constructing)
  {
    BOOST_CHECK_THROW(Circle({10.0, 10.0}, -20.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(MovingToPoint)
  {
    Circle circ({10.0, 10.0}, 10.0);
    rectangle_t circBeforeMoving = circ.getFrameRect();
    double areaBeforeMoving = circ.getArea();

    circ.move( {15.0, 15.0} );
    BOOST_CHECK_EQUAL(circ.getArea(), areaBeforeMoving);
    BOOST_CHECK_EQUAL(circ.getFrameRect().width, circBeforeMoving.width);
    BOOST_CHECK_EQUAL(circ.getFrameRect().height, circBeforeMoving.height);
  }

  BOOST_AUTO_TEST_CASE(RelativeMoving)
  {
    Circle circ({10.0, 10.0}, 10.0);
    rectangle_t circBeforeMoving = circ.getFrameRect();
    double areaBeforeMoving = circ.getArea();

    circ.move( 10.0, 71.0 );
    BOOST_CHECK_EQUAL(circ.getArea(), areaBeforeMoving);
    BOOST_CHECK_EQUAL(circ.getFrameRect().width, circBeforeMoving.width);
    BOOST_CHECK_EQUAL(circ.getFrameRect().height, circBeforeMoving.height);
  }

  BOOST_AUTO_TEST_CASE(InvalidScalingParameter)
  {
    Circle circ({10.0, 10.0}, 56.0);
    BOOST_CHECK_THROW(circ.scale(-10.0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Scaling)
  {
    Circle circ({10.0, 10.0}, 10.0);
    rectangle_t circBeforeScaling = circ.getFrameRect();
    double areaBeforeScaling = circ.getArea();
    circ.scale(10.0);

    BOOST_CHECK_EQUAL(circ.getFrameRect().pos.x, circBeforeScaling.pos.x);
    BOOST_CHECK_EQUAL(circ.getFrameRect().pos.y, circBeforeScaling.pos.y);

    BOOST_CHECK_CLOSE(circ.getFrameRect().height, circBeforeScaling.height * 10.0, EPSILON);
    BOOST_CHECK_CLOSE(circ.getFrameRect().width, circBeforeScaling.width * 10.0, EPSILON);

    BOOST_CHECK_CLOSE(circ.getArea(), areaBeforeScaling * 10.0 * 10.0, EPSILON);
  }
BOOST_AUTO_TEST_SUITE_END()
