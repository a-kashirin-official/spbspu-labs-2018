#define BOOST_TEST_MODULE main_test

#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "base-types.hpp"
#include <stdexcept>

const double DELTA = 0.00001;
const double RADIUS = 10.3;
const double KSCALE = 5.1;

BOOST_AUTO_TEST_SUITE(MoveToPoint)
  BOOST_AUTO_TEST_CASE(MoveRectToPoint)
  {
    revtova::Rectangle rect ({1.1,3.4}, 10.5, 5.5);
    double area = rect.getArea();
    rect.move({3.5, 4.2});
    BOOST_CHECK_CLOSE(rect.getArea(), area, DELTA);
    BOOST_CHECK_CLOSE(rect.getFrameRect().width, 10.5, DELTA);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height, 5.5, DELTA);
  }
  BOOST_AUTO_TEST_CASE(MoveCircToPoint)
  {
    revtova::Circle circ ({1.8, 4.6}, RADIUS);
    double area = circ.getArea();
    circ.move({10.3, 12.6});
    BOOST_CHECK_CLOSE(circ.getArea(), area, DELTA);
    BOOST_CHECK_CLOSE(circ.getFrameRect().height/2, RADIUS, DELTA);
    BOOST_CHECK_CLOSE(circ.getFrameRect().width/2, RADIUS, DELTA);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(MoveToXY)
  BOOST_AUTO_TEST_CASE(MoveRectXY)
  {
    revtova::Rectangle rect ({1.1, 3.5}, 10.6, 5.9);
    double area = rect.getArea();
    rect.move(10.5,5.8);
    BOOST_CHECK_CLOSE(rect.getArea(), area, DELTA);
    BOOST_CHECK_CLOSE(rect.getFrameRect().width, 10.6, DELTA);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height, 5.9, DELTA);
  }
  BOOST_AUTO_TEST_CASE(MoveCircXY)
  {
    revtova::Circle circ ({2.4, 5.6}, RADIUS);
    double area = circ.getArea();
    circ.move(10.3, 11.5);
    BOOST_CHECK_CLOSE(circ.getArea(), area, DELTA);
    BOOST_CHECK_CLOSE(circ.getFrameRect().height/2, RADIUS, DELTA);
    BOOST_CHECK_CLOSE(circ.getFrameRect().width/2, RADIUS, DELTA);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Area)
  BOOST_AUTO_TEST_CASE(RectArea)
  {
    revtova::Rectangle rect ({1.1, 3.4}, 10.5, 5.2);
    double area = rect.getArea();
    rect.scale(KSCALE);
    double new_area = rect.getArea();
    BOOST_CHECK_CLOSE(new_area/area, KSCALE*KSCALE, DELTA);
  }
  BOOST_AUTO_TEST_CASE(CircArea)
  {
    revtova::Circle circ ({2.6, 5.4}, RADIUS);
    double area = circ.getArea();
    circ.scale(KSCALE);
    double new_area = circ.getArea();
    BOOST_CHECK_CLOSE(new_area/area, KSCALE*KSCALE, DELTA);
  }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(IncorrectValue)
  BOOST_AUTO_TEST_CASE(RectIncorInit)
  {
    BOOST_CHECK_THROW(revtova::Rectangle rect ({5.6, 0.6}, -4.4, 3.1), std::invalid_argument);
    BOOST_CHECK_THROW(revtova::Rectangle rect ({5.6, 0.6}, 4.4, -3.1), std::invalid_argument);
    BOOST_CHECK_THROW(revtova::Rectangle rect ({5.6, 0.6}, -4.4, -3.1), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(RectIncorScale)
  {
    revtova::Rectangle rect ({5.6, 0.8}, 4.3, 6.2);
    BOOST_CHECK_THROW(rect.scale(-4.5), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(CircIncorInit)
  {
    BOOST_CHECK_THROW(revtova::Circle circ ({2.6, 5.1}, -3.3), std::invalid_argument);
  }
  BOOST_AUTO_TEST_CASE(CircIncorScale)
  {
    revtova::Circle circ ({0.0, 4.0}, 5.4);
    BOOST_CHECK_THROW(circ.scale(-2.5), std::invalid_argument);
  }
BOOST_AUTO_TEST_SUITE_END()
